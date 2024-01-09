#include <iostream>
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
        cout << "------" << endl;
    }

    ~Matrix()
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] matrix[i];
        }

        delete[] matrix;
    }
};

int main()
{
    Matrix<int> m1(2, 3);
    m1.insertElement(1, 0, 0);
    m1.insertElement(1, 0, 1);
    m1.insertElement(1, 0, 2);
    m1.insertElement(0, 1, 0);
    m1.insertElement(0, 1, 1);
    m1.insertElement(0, 1, 2);
    m1.Print();
    m1.transpose();
    m1.Print();
    Matrix<int> m2(2, 3);
    m2.insertElement(-1, 0, 0);
    m2.insertElement(-1, 0, 1);
    m2.insertElement(-1, 0, 2);
    m2.insertElement(10, 1, 0);
    m2.insertElement(5, 1, 1);
    m2.insertElement(1, 1, 2);
    m2.transpose();
    m2.Print();
    Matrix<int> m3(m2);
    m3.Print();
    Matrix<int> m4(m1 + m3);
    m4.Print();
    m4.transpose();
    m4.Print();

    return 0;
}