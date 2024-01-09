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
        traverseArr.push_back(root->key);
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
            traverseArr.push_back(front->key);
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

void print(vector<int> *traverseArr)
{
    for (int i = 0; i < traverseArr->size(); i++)
    {
        cout << traverseArr->at(i) << ", ";
    }
    cout << endl;
}

int main()
{
    vector<pair<int, int>> arr{{14, 4}, {7, 2}, {15, 12}, {39, 9}, {17, 6}, {25, 8}, {13, 10}};
    SpecialBST<int, int> specialBST;

    for (auto &ele : arr)
    {
        cout << "Inserted (" << ele.first << " " << ele.second << "): " << specialBST.insert(ele.first, ele.second) << endl;
        vector<int> *traverseArr = specialBST.getValuesLevelWise();
        for (int i = 0; i < traverseArr->size(); i++)
        {
            cout << traverseArr->at(i) << ", ";
        }
        cout << endl;
    }

    cout << "\nInOrder: ";
    print(specialBST.getValuesInOrder());

    cout << "\nLevelOrder: ";
    print(specialBST.getValuesLevelWise());

    cout << "Search 17: ";
    int *value = specialBST.search(17);
    cout << (value ? *value : -1) << endl;
    print(specialBST.getValuesLevelWise());
    cout << endl;

    cout << "Search 39: ";
    value = specialBST.search(39);
    cout << (value ? *value : -1) << endl;
    print(specialBST.getValuesLevelWise());
    cout << endl;

    cout << "\nDeleting 14: " << specialBST.deleteKey(14) << endl;
    cout << "Level Order Traversal: ";
    print(specialBST.getValuesLevelWise());

    cout << "\nDeleting 25: " << specialBST.deleteKey(25) << endl;
    cout << "Level Order Traversal: ";
    print(specialBST.getValuesLevelWise());

    cout << "\nDeleting 14: " << specialBST.deleteKey(14) << endl;
    cout << "Level Order Traversal: ";
    print(specialBST.getValuesLevelWise());

    return 0;
}
