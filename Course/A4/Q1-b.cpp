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

class StudentList
{
private:
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

    SpecialBST<int, struct StudentData> bst;

public:
    bool InsertNewStudent(int rollNumber, string firstName, string lastName, int batch, string department, float cgpa)
    {
        struct StudentData student;
        student.rollNumber = rollNumber;
        student.firstName = firstName;
        student.lastName = lastName;
        student.batch = batch;
        student.department = department;
        student.cgpa = cgpa;

        return bst.insert(rollNumber, student);
    }

    bool deleteStudent(int rollNumber)
    {
        return bst.deleteKey(rollNumber);
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
            return bst.insert(newRollNumber, oldStudent);
        }
        else
        {
            if (bst.deleteKey(oldRollNumber))
            {
                return bst.insert(newRollNumber, oldStudent);
            }
            else
            {
                return false; // Student with oldRollNumber not found
            }
        }
    }

    void printAllStudents()
    {
        vector<StudentData> *students = bst.getValuesInOrder();
        for (const auto &student : *students)
        {
            cout << "Roll Number: " << student.rollNumber << ", Name: " << student.firstName << " " << student.lastName
                 << ", Batch: " << student.batch << ", Department: " << student.department << ", CGPA: " << student.cgpa << endl;
        }
    }
};

int main()
{
    StudentList studentList;

    studentList.InsertNewStudent(1011, "Aashir", "Israr", 2023, "CS", 3.8);
    studentList.InsertNewStudent(1021, "Abdullah", "Nasir", 2022, "EE", 3.7);
    studentList.InsertNewStudent(1034, "Ahmed", "Khan", 2024, "CS", 3.3);

    cout << "All Students:" << endl;
    studentList.printAllStudents();

    studentList.updateStudent(1021, 1055, "Mustafa", "Ali", 2022, "ME", 3.5);

    cout << "\nStudents After Updation:" << endl;
    studentList.printAllStudents();

    studentList.deleteStudent(1011);

    cout << "\nStudents After Deletion:" << endl;
    studentList.printAllStudents();

    return 0;
}
