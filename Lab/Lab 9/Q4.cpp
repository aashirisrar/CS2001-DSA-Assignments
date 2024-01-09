#include <iostream>
using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

class BST
{
private:
    TreeNode *root;

    TreeNode *insertRecursive(TreeNode *node, int key)
    {
        if (node == nullptr)
        {
            return new TreeNode(key);
        }

        if (key < node->val)
        {
            node->left = insertRecursive(node->left, key);
        }
        else if (key > node->val)
        {
            node->right = insertRecursive(node->right, key);
        }

        return node;
    }

    TreeNode *findMinNode(TreeNode *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    TreeNode *deleteRecursive(TreeNode *node, int key)
    {
        if (node == nullptr)
        {
            return node;
        }

        if (key < node->val)
        {
            node->left = deleteRecursive(node->left, key);
        }
        else if (key > node->val)
        {
            node->right = deleteRecursive(node->right, key);
        }
        else
        {
            if (node->left == nullptr)
            {
                TreeNode *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                TreeNode *temp = node->left;
                delete node;
                return temp;
            }

            TreeNode *temp = findMinNode(node->right);
            node->val = temp->val;
            node->right = deleteRecursive(node->right, temp->val);
        }
        return node;
    }

public:
    BST() : root(nullptr) {}

    void insert(int key)
    {
        root = insertRecursive(root, key);
    }

    void remove(int key)
    {
        root = deleteRecursive(root, key);
    }

    void inOrder(TreeNode *root)
    {
        if (root == NULL)
        {
            return;
        }

        inOrder(root->left);
        cout << root->val << " ";
        inOrder(root->right);
    }

    void inOrder()
    {
        inOrder(root);
        cout << endl;
    }
};

int main()
{
    BST bST;

    bST.insert(1);
    bST.insert(2);
    bST.insert(3);

    cout << "After Insertion:" << endl;
    bST.inOrder();

    bST.remove(3);

    cout << "After Removal:" << endl;
    bST.inOrder();
}