#include <iostream>
using namespace std;

template <class T>
class BinaryTree
{
    class Node
    {
    public:
        Node *left;
        Node *right;
        T data;

        Node(T data)
        {
            this->data = data;
            left = NULL;
            right = NULL;
        }
    };

    Node *root;

public:
    BinaryTree()
    {
        root = NULL;
    }

    void insert(T key)
    {
        root = insertRecursive(root, key);
    }

    Node *insertRecursive(Node *root, T key)
    {
        if (root == NULL)
        {
            return new Node(key);
        }

        if (key < root->data)
        {
            root->left = insertRecursive(root->left, key);
        }
        else if (key > root->data)
        {
            root->right = insertRecursive(root->right, key);
        }

        return root;
    }

    bool search(T key)
    {
        return searchRecursive(root, key);
    }

    bool searchRecursive(Node *root, T key)
    {
        if (root == NULL)
        {
            return false;
        }

        if (root->data == key)
        {
            return true;
        }

        return searchRecursive(root->left, key) || searchRecursive(root->right, key);
    }

    void preOrder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }

        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }

    void preOrder()
    {
        preOrder(root);
        cout << endl;
    }
};

int main()
{
    BinaryTree<int> bT;

    bT.insert(1);
    bT.insert(2);
    bT.insert(3);

    bT.preOrder();

    if (bT.search(3))
    {
        cout << "Key 3 found." << endl;
    }
    else
    {
        cout << "Key 3 not found." << endl;
    }

    return 0;
}
