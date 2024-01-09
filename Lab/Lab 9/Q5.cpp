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

    void inOrder(TreeNode *node) const
    {
        if (node == nullptr)
        {
            return;
        }
        inOrder(node->left);
        cout << node->val << " ";
        inOrder(node->right);
    }

    void inOrder() const
    {
        inOrder(root);
        cout << endl;
    }

    int getCount(TreeNode *node, int low, int high) const
    {
        if (!node)
        {
            return 0;
        }

        if (node->val == high && node->val == low)
        {
            return 1;
        }

        if (node->val <= high && node->val >= low)
        {
            return 1 + getCount(node->left, low, high) + getCount(node->right, low, high);
        }
        else if (node->val < low)
        {
            return getCount(node->right, low, high);
        }
        else
        {
            return getCount(node->left, low, high);
        }
    }

    int getCount(int low, int high) const
    {
        return getCount(root, low, high);
    }
};

int main()
{
    BST bST;

    bST.insert(1);
    bST.insert(2);
    bST.insert(3);
    bST.insert(5);
    bST.insert(6);

    cout << "After Insertion:" << endl;
    bST.inOrder();

    cout << "Count of Nodes in the range:" << bST.getCount(2, 5) << endl;
}
