#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

class Node
{
public:
    string key, meaning;
    Node *left;
    Node *right;
    int height;

    Node(string k, string m)
    {
        key = k;
        meaning = m;
        left = right = nullptr;
        height = 1;
    }
};

class AVL
{
private:
    Node *root;

    int height(Node *n)
    {
        return n ? n->height : 0;
    }

    int getBalance(Node *n)
    {
        return n ? height(n->left) - height(n->right) : 0;
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node *insert(Node *node, string key, string meaning)
    {
        if (!node)
            return new Node(key, meaning);
        if (key < node->key)
            node->left = insert(node->left, key, meaning);
        else if (key > node->key)
            node->right = insert(node->right, key, meaning);
        else
        {
            cout << "Keyword already exists. Use update to change meaning.\n";
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node *deleteNode(Node *root, string key)
    {
        if (!root)
            return root;
        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else
        {
            if (!root->left || !root->right)
            {
                Node *temp = root->left ? root->left : root->right;
                if (!temp)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else
            {
                Node *temp = minValueNode(root->right);
                root->key = temp->key;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (!root)
            return root;

        root->height = max(height(root->left), height(root->right)) + 1;
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    Node *search(Node *root, string key, int &comparisons)
    {
        if (!root)
            return nullptr;
        comparisons++;
        if (key == root->key)
            return root;
        else if (key < root->key)
            return search(root->left, key, comparisons);
        else
            return search(root->right, key, comparisons);
    }

    void inorder(Node *root)
    {
        if (root)
        {
            inorder(root->left);
            cout << root->key << " : " << root->meaning << "\n";
            inorder(root->right);
        }
    }

    void reverseInorder(Node *root)
    {
        if (root)
        {
            reverseInorder(root->right);
            cout << root->key << " : " << root->meaning << "\n";
            reverseInorder(root->left);
        }
    }

    void update(Node *root, string key, string newMeaning)
    {
        int dummy = 0;
        Node *found = search(root, key, dummy);
        if (found)
        {
            found->meaning = newMeaning;
            cout << "Meaning updated.\n";
        }
        else
        {
            cout << "Keyword not found.\n";
        }
    }

    int countNodes(Node *node)
    {
        if (!node)
            return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

public:
    AVL()
    {
        root = nullptr;
    }

    void insert(string key, string meaning)
    {
        root = insert(root, key, meaning);
    }

    void deleteKey(string key)
    {
        root = deleteNode(root, key);
    }

    void update(string key, string meaning)
    {
        update(root, key, meaning);
    }

    void search(string key)
    {
        int comparisons = 0;
        Node *result = search(root, key, comparisons);
        if (result)
            cout << "Found: " << result->key << " => " << result->meaning << " (Comparisons: " << comparisons << ")\n";
        else
            cout << "Keyword not found. Comparisons made: " << comparisons << "\n";
    }

    void displayAscending()
    {
        cout << "\nDictionary in Ascending Order:\n";
        inorder(root);
    }

    void displayDescending()
    {
        cout << "\nDictionary in Descending Order:\n";
        reverseInorder(root);
    }

    void maxComparisons()
    {
        int n = countNodes(root);
        int maxComp = ceil(log2(n + 1));
        cout << "Maximum comparisons in worst-case search: " << maxComp << "\n";
    }
};

int main()
{
    AVL dict;
    int choice, num;
    string key, meaning;
    do
    {
        cout << "\n1. Insert\n2. Delete\n3. Update\n4. Search\n5. Display Ascending\n6. Display Descending\n7. Max Comparisons\n8. Exit\nChoice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter no. of keywords to insert: ";
            cin >> num;
            cin.ignore();
            for (int i = 0; i < num; i++)
            {
                cout << "Enter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                dict.insert(key, meaning);
            }
            break;
        case 2:
            cout << "Enter keyword to delete: ";
            cin >> key;
            dict.deleteKey(key);
            break;
        case 3:
            cout << "Enter keyword to update: ";
            cin >> key;
            cout << "Enter new meaning: ";
            cin.ignore();
            getline(cin, meaning);
            dict.update(key, meaning);
            break;
        case 4:
            cout << "Enter keyword to search: ";
            cin >> key;
            dict.search(key);
            break;
        case 5:
            dict.displayAscending();
            break;
        case 6:
            dict.displayDescending();
            break;
        case 7:
            dict.maxComparisons();
            break;
        case 8:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 8);
    return 0;
}
