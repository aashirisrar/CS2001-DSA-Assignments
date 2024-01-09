#include <iostream>
#include <vector>
using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

void inorderHelper(TreeNode *root, vector<int> &result)
{
    if (root == nullptr)
    {
        return;
    }

    inorderHelper(root->left, result);
    result.push_back(root->val);
    inorderHelper(root->right, result);
}
vector<int> inorderTraversal(TreeNode *root)
{
    vector<int> result;
    inorderHelper(root, result);
    return result;
}

int main()
{
    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);

    vector<int> sorted = inorderTraversal(root);

    for (int num : sorted)
    {
        cout << num << " ";
    }

    return 0;
}
