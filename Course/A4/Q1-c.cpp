#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template <class K, class V>
class SpecialBST
{
private:
    class Node
    {
    public:
        K key;
        V value;
        Node *left;
        Node *right;
    };

    Node *root;
    bool newNodeInserted;
    bool keyFound;
    vector<V> traverseArr;

public:
    SpecialBST() { root = NULL; };

    ~SpecialBST()
    {
        destroyTree(root);
    };

    bool insert(K key, V value)
    {
        newNodeInserted = false;
        root = insertHelper(root, key, value);
        return newNodeInserted;
    };

    V *search(K key)
    {
        keyFound = false;
        root = searchHelper(root, key);
        if (keyFound)
            return &(root->value);
        return NULL;
    }

    bool deleteKey(K key)
    {
        keyFound = false;
        root = deleteHelper(root, key);
        return keyFound;
    }

    vector<V> *getValuesInOrder()
    {
        traverseArr.clear();
        inOrderHelper(root);
        return &traverseArr;
    }

    vector<V> *getValuesLevelWise()
    {
        traverseArr.clear();
        levelOrderHelper(root);
        return &traverseArr;
    }

private:
    Node *insertHelper(Node *root, K key, V value)
    {
        if (root == NULL)
        {
            Node *newNode = new Node;
            newNode->key = key;
            newNode->value = value;
            newNode->left = newNode->right = NULL;
            newNodeInserted = true;
            return newNode;
        }
        if (root->key == key)
            return root;
        if (key < root->key)
        {
            Node *newNode = insertHelper(root->left, key, value);

            root->left = newNode->right;
            newNode->right = root;
            return newNode;
        }
        else
        {
            Node *newNode = insertHelper(root->right, key, value);
            root->right = newNode->left;
            newNode->left = root;
            return newNode;
        }
    }

    void inOrderHelper(Node *root)
    {
        if (root == NULL)
            return;
        inOrderHelper(root->left);
        traverseArr.push_back(root->value);
        inOrderHelper(root->right);
    }

    void levelOrderHelper(Node *root)
    {
        if (root == NULL)
            return;
        queue<Node *> que;
        que.push(root);

        while (!que.empty())
        {
            Node *front = que.front();
            que.pop();
            traverseArr.push_back(front->value);
            if (front->left != NULL)
                que.push(front->left);
            if (front->right != NULL)
                que.push(front->right);
        }
    }

    Node *searchHelper(Node *root, K key)
    {
        if (root == NULL)
            return NULL;
        if (root->key == key)
        {
            keyFound = true;
            return root;
        }
        if (key < root->key)
        {
            Node *node = searchHelper(root->left, key);
            if (node == NULL)
                return root;
            root->left = node->right;
            node->right = root;
            return node;
        }
        else
        {
            Node *node = searchHelper(root->right, key);
            if (node == NULL)
                return root;
            root->right = node->left;
            node->left = root;
            return node;
        }
    }

    Node *deleteHelper(Node *root, K key)
    {
        if (root == NULL)
            return NULL;
        if (key < root->key)
        {
            Node *node = deleteHelper(root->left, key);
            if (keyFound)
            {
                root->left = node;
                return root;
            }
            if (node == NULL)
                return root;
            root->left = node->right;
            node->right = root;
            return node;
        }
        else if (root->key < key)
        {
            Node *node = deleteHelper(root->right, key);
            if (keyFound)
            {
                root->right = node;
                return root;
            }
            if (node == NULL)
                return root;
            root->right = node->left;
            node->left = root;
            return node;
        }
        else
        {
            keyFound = true;
            if (root->right == NULL)
            {
                Node *left_child = root->left;
                delete root;
                return left_child;
            }

            Node *nextLargestNode = smallestNodeGetter(root->right);
            root->key = nextLargestNode->key;
            root->value = nextLargestNode->value;
            root->right = deleteHelper(root->right, nextLargestNode->key);
            return root;
        }
    }

    Node *smallestNodeGetter(Node *root)
    {
        while (root != NULL && root->left != NULL)
            root = root->left;
        return root;
    }

    void destroyTree(Node *root)
    {
        if (root == NULL)
            return;
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    }
};

class StudentData
{
public:
    int rollNumber;
    string firstName;
    string lastName;
    int batch;
    string department;
    float cgpa;

    bool operator<(const StudentData &other) const
    {
        return rollNumber < other.rollNumber;
    }
};

class StudentList
{
private:
    SpecialBST<int, struct StudentData> specialBST;

public:
    bool InsertNewStudent(int rollNumber, string firstName, string lastName, int batch, string department, float cgpa)
    {
        StudentData student;
        student.rollNumber = rollNumber;
        student.firstName = firstName;
        student.lastName = lastName;
        student.batch = batch;
        student.department = department;
        student.cgpa = cgpa;

        return specialBST.insert(rollNumber, student);
    }

    bool deleteStudent(int rollNumber)
    {
        return specialBST.deleteKey(rollNumber);
    }

    bool updateStudent(int oldRollNumber, int newRollNumber, string newFirstName, string newLastName, int newBatch, string newDepartment, float newCgpa)
    {
        StudentData oldStudent;
        oldStudent.rollNumber = oldRollNumber;
        oldStudent.firstName = newFirstName;
        oldStudent.lastName = newLastName;
        oldStudent.batch = newBatch;
        oldStudent.department = newDepartment;
        oldStudent.cgpa = newCgpa;

        if (oldRollNumber == newRollNumber)
        {
            return specialBST.insert(newRollNumber, oldStudent);
        }
        else
        {
            if (specialBST.deleteKey(oldRollNumber))
            {
                return specialBST.insert(newRollNumber, oldStudent);
            }
            else
            {
                return false;
            }
        }
    }

    void printAllStudents()
    {
        vector<StudentData> *students = specialBST.getValuesInOrder();
        cout << "Total Students: " << students->size() << endl;
        for (const auto &student : *students)
        {
            cout << "Roll Number: " << student.rollNumber << ", Name: " << student.firstName << " " << student.lastName
                 << ", Batch: " << student.batch << ", Department: " << student.department << ", CGPA: " << student.cgpa << endl;
        }
    }

    StudentData *searchStudent(int rollNumber)
    {
        return specialBST.search(rollNumber);
    }
};

int main()
{
    StudentList studentList;

    char c;
    do
    {
        cout << "Press I to insert a new student." << endl;
        cout << "Press D to delete a student." << endl;
        cout << "Press S to search a student by roll number." << endl;
        cout << "Press U to update the data of a student." << endl;
        cout << "Press P to print all students sorted by roll number." << endl;
        cout << "Press E to exit." << endl;

        cout << "> ";
        cin >> c;
        c = toupper(c);

        switch (c)
        {
        case 'I':
        {
            int rollNumber, batch;
            string firstName, lastName, department;
            float cgpa;

            cout << "Please enter the data of new student in the order:\n Roll Number, First Name, Last Name, Batch, Department, CGPA:" << endl;
            cout << "> ";
            cin >> rollNumber >> firstName >> lastName >> batch >> department >> cgpa;

            if (studentList.InsertNewStudent(rollNumber, firstName, lastName, batch, department, cgpa))
            {
                cout << "New student inserted successfully!" << endl;
            }
            else
            {
                cout << "Failed to insert the student. Duplicate roll number detected." << endl;
            }

            break;
        }
        case 'D':
        {
            int rollNumber;

            cout << "Please enter the roll number of the student to delete:" << endl;
            cout << "> ";
            cin >> rollNumber;

            if (studentList.deleteStudent(rollNumber))
            {
                cout << "Student deleted successfully!" << endl;
            }
            else
            {
                cout << "Student with the given roll number not found." << endl;
            }

            break;
        }
        case 'S':
        {
            int rollNumber;

            cout << "Please enter the roll number of the student to search:" << endl;
            cout << "> ";
            cin >> rollNumber;

            StudentData *student = studentList.searchStudent(rollNumber);

            if (student != nullptr)
            {
                cout << "Student found:" << endl;
                cout << "Roll Number: " << student->rollNumber << ", Name: " << student->firstName << " " << student->lastName
                     << ", Batch: " << student->batch << ", Department: " << student->department << ", CGPA: " << student->cgpa << endl;
            }
            else
            {
                cout << "Student with the given roll number not found." << endl;
            }

            break;
        }
        case 'U':
        {
            int oldRollNumber, newRollNumber, newBatch;
            string newFirstName, newLastName, newDepartment;
            float newCgpa;

            cout << "Please enter the data for updating the student in the order: Old Roll Number, New Roll Number, New First Name, New Last Name, New Batch, New Department, New CGPA" << endl;
            cout << "> ";
            cin >> oldRollNumber >> newRollNumber >> newFirstName >> newLastName >> newBatch >> newDepartment >> newCgpa;

            if (studentList.updateStudent(oldRollNumber, newRollNumber, newFirstName, newLastName, newBatch, newDepartment, newCgpa))
            {
                cout << "Student data updated successfully!" << endl;
            }
            else
            {
                cout << "Failed to update student data. Student with the old roll number not found." << endl;
            }

            break;
        }
        case 'P':
        {
            studentList.printAllStudents();
            break;
        }
        case 'E':
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid c. Please enter a valid option." << endl;
        }

    } while (c != 'E');

    return 0;
}
