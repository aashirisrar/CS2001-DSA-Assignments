#include <iostream>
#include <algorithm>

template <typename T>
struct Node
{
    T key;
    int height;
    Node *left;
    Node *right;

    Node(T k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

template <typename T>
class AVL
{
private:
    Node<T> *root;

    int getHeight(Node<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }

    int getBalanceFactor(Node<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    Node<T> *rightRotate(Node<T> *y)
    {
        Node<T> *x = y->left;
        Node<T> *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node<T> *leftRotate(Node<T> *x)
    {
        Node<T> *y = x->right;
        Node<T> *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node<T> *insertNode(Node<T> *node, T key)
    {
        if (node == nullptr)
        {
            return new Node<T>(key);
        }

        if (key < node->key)
        {
            node->left = insertNode(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = insertNode(node->right, key);
        }
        else
        {
            return node; // Duplicate keys not allowed
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && key < node->left->key)
        {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && key > node->right->key)
        {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node<T> *deleteNode(Node<T> *node, T key)
    {
        if (node == nullptr)
        {
            return node;
        }

        if (key < node->key)
        {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = deleteNode(node->right, key);
        }
        else
        {
            if (node->left == nullptr || node->right == nullptr)
            {
                Node<T> *temp = (node->left != nullptr) ? node->left : node->right;

                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                {
                    *node = *temp;
                }

                delete temp;
            }
            else
            {
                Node<T> *temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = deleteNode(node->right, temp->key);
            }
        }

        if (node == nullptr)
        {
            return node;
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && getBalanceFactor(node->left) >= 0)
        {
            return rightRotate(node);
        }

        // Left Right Case
        if (balance > 1 && getBalanceFactor(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && getBalanceFactor(node->right) <= 0)
        {
            return leftRotate(node);
        }

        // Right Left Case
        if (balance < -1 && getBalanceFactor(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node<T> *minValueNode(Node<T> *node)
    {
        Node<T> *current = node;
        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    void inorderTraversal(Node<T> *node)
    {
        if (node != nullptr)
        {
            inorderTraversal(node->left);
            std::cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }

    void preorderTraversal(Node<T> *node)
    {
        if (node != nullptr)
        {
            std::cout << node->key << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }

    void postorderTraversal(Node<T> *node)
    {
        if (node != nullptr)
        {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            std::cout << node->key << " ";
        }
    }

    void printPathsUtil(Node<T> *node, T path[], int pathLength)
    {
        if (node == nullptr)
        {
            return;
        }

        path[pathLength] = node->key;
        ++pathLength;

        if (node->left == nullptr && node->right == nullptr)
        {
            printArray(path, pathLength);
        }
        else
        {
            printPathsUtil(node->left, path, pathLength);
            printPathsUtil(node->right, path, pathLength);
        }
    }

    void printArray(T ints[], int len)
    {
        for (int i = 0; i < len; ++i)
        {
            std::cout << ints[i] << " ";
        }
        std::cout << std::endl;
    }

public:
    AVL() : root(nullptr) {}

    void insert(T key)
    {
        root = insertNode(root, key);
    }

    Node<T> *deleteNode(T key)
    {
        return deleteNode(root, key);
    }

    void displayInorder()
    {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    void displayPreorder()
    {
        preorderTraversal(root);
        std::cout << std::endl;
    }

    void displayPostorder()
    {
        postorderTraversal(root);
        std::cout << std::endl;
    }

    bool search(T key)
    {
        Node<T> *current = root;
        while (current != nullptr)
        {
            if (key == current->key)
            {
                return true;
            }
            else if (key < current->key)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return false;
    }

    Node<T> *getRoot() const
    {
        return root;
    }

    void printAllPaths()
    {
        T path[100];
        printPathsUtil(root, path, 0);
    }
};

int main()
{
    AVL<int> avlTree;

    // Inserting elements into the AVL tree
    avlTree.insert(10);
    avlTree.insert(20);
    avlTree.insert(30);
    avlTree.insert(40);
    avlTree.insert(50);
    avlTree.insert(25);

    // Displaying different traversals
    std::cout << "Inorder traversal: ";
    avlTree.displayInorder();

    std::cout << "Preorder traversal: ";
    avlTree.displayPreorder();

    std::cout << "Postorder traversal: ";
    avlTree.displayPostorder();

    // Checking if an element exists in the tree
    int searchKey = 30;
    if (avlTree.search(searchKey))
    {
        std::cout << searchKey << " exists in the AVL tree." << std::endl;
    }
    else
    {
        std::cout << searchKey << " doesn't exist in the AVL tree." << std::endl;
    }

    // Deleting an element from the AVL tree
    int deleteKey = 20;
    avlTree.deleteNode(deleteKey);

    // Displaying the tree after deletion
    std::cout << "Inorder traversal after deleting " << deleteKey << ": ";
    avlTree.displayInorder();

    // Printing all root-to-leaf paths
    std::cout << "Root-to-leaf paths: " << std::endl;
    avlTree.printAllPaths();

    return 0;
}
