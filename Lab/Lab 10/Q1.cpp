#include <iostream>
#include <queue>

struct Node
{
    int data;
    Node *left;
    Node *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST
{
private:
    Node *root;

    Node *insertRecursive(Node *curr, int value)
    {
        if (curr == nullptr)
        {
            return new Node(value);
        }

        if (value < curr->data)
        {
            curr->left = insertRecursive(curr->left, value);
        }
        else if (value > curr->data)
        {
            curr->right = insertRecursive(curr->right, value);
        }
        else
        {
            return curr; // If the value already exists, return the node
        }

        return curr;
    }

    Node *copyTree(Node *original)
    {
        if (original == nullptr)
        {
            return nullptr;
        }

        Node *newNode = new Node(original->data);
        newNode->left = copyTree(original->left);
        newNode->right = copyTree(original->right);
        return newNode;
    }

    void inorderTraversal(Node *node) const
    {
        if (node == nullptr)
        {
            return;
        }

        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }

    void levelOrderTraversal() const
    {
        if (root == nullptr)
        {
            return;
        }

        std::queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i)
            {
                Node *current = q.front();
                q.pop();
                std::cout << current->data << " ";
                if (current->left != nullptr)
                {
                    q.push(current->left);
                }
                if (current->right != nullptr)
                {
                    q.push(current->right);
                }
            }
            std::cout << std::endl; // Move to the next level
        }
    }

    Node *searchRecursive(Node *curr, int key)
    {
        if (curr == nullptr || curr->data == key)
        {
            return curr;
        }

        if (key < curr->data)
        {
            return searchRecursive(curr->left, key);
        }
        else
        {
            return searchRecursive(curr->right, key);
        }
    }

    int countNodesRecursive(Node *node) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        return 1 + countNodesRecursive(node->left) + countNodesRecursive(node->right);
    }

    int leafCountRecursive(Node *node) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        if (node->left == nullptr && node->right == nullptr)
        {
            return 1;
        }
        return leafCountRecursive(node->left) + leafCountRecursive(node->right);
    }

    void deleteTree(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }

        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    bool insert(int value)
    {
        if (search(value) != nullptr)
        {
            return false; // Value already exists in the tree
        }
        root = insertRecursive(root, value);
        return true;
    }

    BST(const BST &other)
    {
        root = copyTree(other.root);
    }

    ~BST()
    {
        deleteTree(root);
    }

    void inorderPrint() const
    {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    void levelorderPrint() const
    {
        levelOrderTraversal();
    }

    Node *search(int key)
    {
        return searchRecursive(root, key);
    }

    int countNodes() const
    {
        return countNodesRecursive(root);
    }

    int leafCount() const
    {
        return leafCountRecursive(root);
    }
};

int main()
{
    BST bst;

    // Inserting elements into the BST
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    // Printing inorder traversal
    std::cout << "Inorder traversal: ";
    bst.inorderPrint();

    // Printing level-order traversal
    std::cout << "Level-order traversal:" << std::endl;
    bst.levelorderPrint();

    // Searching for elements in the BST
    int keyToSearch = 40;
    Node *foundNode = bst.search(keyToSearch);
    if (foundNode != nullptr)
    {
        std::cout << "Found node with key " << keyToSearch << std::endl;
    }
    else
    {
        std::cout << "Node with key " << keyToSearch << " not found" << std::endl;
    }

    // Counting total nodes and leaf nodes
    std::cout << "Total nodes in the BST: " << bst.countNodes() << std::endl;
    std::cout << "Leaf nodes in the BST: " << bst.leafCount() << std::endl;

    return 0;
}
