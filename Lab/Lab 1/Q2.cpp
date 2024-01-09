#include <iostream>
#include <cstring>
using namespace std;

template <class T>
class Matrix
{
    T **matrix;
    int rows, cols;

public:
    Matrix(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;

        matrix = new T *[rows];
        for (int i = 0; i < rows; i++)
        {
            matrix[i] = new T[cols];
        }
    }

    Matrix(Matrix const &obj)
    {
        rows = obj.rows;
        cols = obj.cols;

        matrix = new T *[rows];
        for (int i = 0; i < rows; i++)
        {
            matrix[i] = new T[cols];
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                matrix[i][j] = obj.matrix[i][j];
            }
        }
    }

    void operator=(Matrix const &obj)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                matrix[i][j] = obj.matrix[i][j];
            }
        }
    }

    void insertElement(T const &element, int rowNum, int colNum)
    {
        matrix[rowNum][colNum] = element;
    }

    Matrix<T> operator+(Matrix const &obj)
    {
        Matrix<T> resMat(rows, cols);
        if (rows == obj.rows && cols == obj.cols)
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    resMat.matrix[i][j] = matrix[i][j] + obj.matrix[i][j];
                }
            }

            return resMat;
        }
        else
        {
            cout << "Error" << endl;
            return resMat;
        }
    }

    void transpose()
    {
        T **temp = new T *[rows];
        for (int i = 0; i < rows; i++)
        {
            temp[i] = new T[cols];
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                temp[i][j] = matrix[i][j];
            }
        }
        if (rows == cols)
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    matrix[i][j] = temp[j][i];
                }
            }
        }
        else
        {
            for (int i = 0; i < rows; i++)
            {
                delete matrix[i];
            }
            delete[] matrix;

            int tempRow = rows;
            rows = cols;
            cols = tempRow;
            matrix = new T *[rows];
            for (int i = 0; i < rows; i++)
            {
                matrix[i] = new T[cols];
            }

            int l = 0;
            int m = 0;
            for (int i = 0; i < cols; i++)
            {
                l = 0;
                for (int j = 0; j < rows; j++)
                {
                    matrix[l++][m] = temp[i][j];
                }
                m++;
            }
        }
    }

    void Print()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    ~Matrix()
    {
    }
};

template <>
class Matrix<char *>
{
    int rows;
    int cols;
    char ***matrix;

public:
    Matrix(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;

        matrix = new char **[rows];
        for (int i = 0; i < rows; i++)
        {
            matrix[i] = new char *[cols];
            for (int j = 0; j < cols; ++j)
            {
                matrix[i][j] = NULL;
            }
        }
    }

    void insertElement(char *const &element, int rowNum, int colNum)
    {
        int len = strlen(element);
        delete[] matrix[rowNum][colNum];
        matrix[rowNum][colNum] = new char[len + 1];
        strcpy(matrix[rowNum][colNum], element);
    }

    Matrix<char *> &operator=(Matrix<char *> const &obj)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; ++j)
            {
                int len = strlen(obj.matrix[i][j]);
                delete[] matrix[i][j];
                matrix[i][j] = new char[len + 1];
                strcpy_s(matrix[i][j], len + 1, obj.matrix[i][j]);
            }
        }

        return *this;
    }

    void transpose()
    {
        if (rows == cols && rows != 1)
        {

            char ***temp = new char **[rows];
            for (int i = 0; i < rows; i++)
            {
                temp[i] = new char *[cols];
                for (int j = 0; j < cols; j++)
                {
                    int len = strlen(matrix[i][j]);
                    temp[i][j] = new char[len + 1];
                }
            }

            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    temp[i][j] = matrix[i][j];
                }
            }

            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    matrix[i][j] = temp[j][i];
                }
            }
        }
    }

    Matrix<char *> operator+(Matrix const &obj)
    {
        Matrix<char *> resMat(rows, cols);

        if (rows == obj.rows && cols == obj.cols)
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    int len1 = strlen(matrix[i][j]);
                    int len2 = strlen(obj.matrix[i][j]);
                    int totalLen = len1 + len2;
                    delete[] resMat.matrix[i][j];
                    resMat.matrix[i][j] = new char[totalLen + 1];
                    strcpy(resMat.matrix[i][j], matrix[i][j]);
                    strcat(resMat.matrix[i][j], obj.matrix[i][j]);
                }
            }
        }
        else
        {
            cout << "Error" << endl;
        }

        return resMat;
    }

    void print()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << "---------------------------" << endl;
    }

    ~Matrix()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; ++j)
            {
                delete[] matrix[i][j];
            }
            delete[] matrix[i];
        }
        delete[] matrix;
    }
};

int main()
{
    Matrix<char *> mA(2, 2);
    mA.insertElement((char *)"Computer", 0, 0);
    mA.insertElement((char *)"Electrical", 0, 1);
    mA.insertElement((char *)"Business", 1, 0);
    mA.insertElement((char *)"Civil", 1, 1);
    mA.print();
    Matrix<char *> mB(2, 2);
    mB.insertElement((char *)"Science", 0, 0);
    mB.insertElement((char *)"Engineering", 0, 1);
    mB.insertElement((char *)"Administration", 1, 0);
    mB.insertElement((char *)"Engineering", 1, 1);
    mB.print();
    Matrix<char *> mC(1, 1);
    mC = mA + mB;
    mC.transpose();
    mC.print();
}