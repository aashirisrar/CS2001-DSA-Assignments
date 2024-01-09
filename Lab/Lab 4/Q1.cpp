#include <iostream>
using namespace std;

class Node
{
public:
    Node *right;
    Node *left;
    int data;

    Node(int data)
    {
        this->data = data;
        right = nullptr;
        left = nullptr;
    }
};

void flatten(Node *root)
{
    if (root == NULL || (root->left == NULL && root->right == NULL))
    {
        return;
    }
    if (root->left != NULL)
    {
        flatten(root->left);

        Node *temp = root->right;
        root->right = root->left;
        root->left = NULL;

        Node *t = root->right;
        while (t->right != NULL)
        {
            t = t->right;
        }
        t->right = temp;
    }

    flatten(root->right);
}

void print(Node *head)
{
    Node *current = head;
    while (current)
    {
        cout << current->data << "->";
        current = current->right;
    }
    cout << "NULL" << endl;
}

int main()
{
    Node *head = new Node(1);
    head->right = new Node(2);
    head->right->left = new Node(5);
    head->right->right = new Node(3);
    head->right->right->right = new Node(4);
    head->right->left->right = new Node(6);
    head->right->left->left = new Node(7);
    head->right->left->left->right = new Node(8);

    flatten(head);
    cout << "Flattened Linked List:" << endl;
    print(head);

    return 0;
}
