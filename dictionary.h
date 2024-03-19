#ifndef DICTIONARY
#define DICTIONARY
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Dictionary class that uses an AVL tree for storage
template <typename Key, typename Info>
class Dictionary {
private:
    // Node structure for AVL tree
    struct Node {
        Key key;       // Key of the node
        Info info;     // Information associated with the key
        Node* left;    // Left child node
        Node* right;   // Right child node
        int height;    // Height of the node

        Node(Key key, Info info) : key(key), info(info), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root; // Root of the AVL tree

    // Function to get height of a node
    int height(Node* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    // Function to perform right rotation on a node
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x; // new root
    }

    // Function to perform left rotation on a node
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y; // new root
    }

    // Function to get the balance factor of a node
    int getBalance(Node* N) {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }

    // Function to insert a new key and info in the AVL tree
    Node* insert(Node* node, Key key, Info info) {
        if (node == nullptr)
            return(new Node(key, info));

        if (key < node->key)
            node->left = insert(node->left, key, info);
        else if (key > node->key)
            node->right = insert(node->right, key, info);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Function to print the AVL tree in inorder
    void printInOrder(Node* node) {
        if (node != nullptr) {
            printInOrder(node->left);
            cout << "Key: " << node->key << " Info: " << node->info << endl;
            printInOrder(node->right);
        }
    }

    // Function to remove a node with a given key
    Node* remove(Node* root, Key key) {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = remove(root->left, key);
        else if(key > root->key)
            root->right = remove(root->right, key);
        else {
            // node with only one child or no child
            if((root->left == nullptr) || (root->right == nullptr)) {
                Node *temp = root->left ? root->left : root->right;

                // No child case
                if(temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else // One child case
                    *root = *temp; // Copy the contents of the non-empty child

                delete temp;
            }
            else {
                // node with two children: Get the inorder successor (smallest in the right subtree)
                Node* temp = minValueNode(root->right);

                // Copy the inorder successor's data to this node
                root->key = temp->key;
                root->info = temp->info;

                // Delete the inorder successor
                root->right = remove(root->right, temp->key);
            }
        }

        // If the tree had only one node then return
        if (root == nullptr)
            return root;

        // Update height of the current node
        root->height = 1 + max(height(root->left), height(root->right));

        // Get the balance factor
        int balance = getBalance(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    // Function to find the node with minimum key value
    Node* minValueNode(Node* node) {
        Node* current = node;

        // loop down to find the leftmost leaf
        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    // Function to find the node with maximum key (rightmost node)
    Node* findMax(Node* node) {
        Node* current = node;

        /* loop down to find the rightmost leaf */
        while (current->right != nullptr)
            current = current->right;

        return current;
    }

    void graphAux(int indent, Node* subtreeRoot) {
        if (subtreeRoot != nullptr) {
            graphAux(indent + 8, subtreeRoot->right);
            cout << setw(indent) << " " << subtreeRoot->key << endl;
            cout << setw(indent) << " " << subtreeRoot->info << endl;
            graphAux(indent + 8, subtreeRoot->left);
        }
    }

public:
    long long amount = 0;

    Dictionary() : root(nullptr) {}

    ~Dictionary() {
        delete root;
    }

    // Function to insert a new key and info
    void insertNode(Key key, Info info) {
        root = insert(root, key, info);
        amount++;
    }

    // Function to print the AVL tree
    void print() {
        printInOrder(root);
    }

    // Function to remove the node with maximum key
    void removeLast() {
        if (root == nullptr) {
            cout << "No nodes to remove." << endl;
            return;
        }
        Node* last = findMax(root);
        root = remove(root, last->key);
        amount--;
    }

    // Function to display the AVL tree as a graph
    void graph() {
        if (root == nullptr) {
            cout << "Dictionary is empty." << endl;
            return;
        }
        graphAux(0, root);
    }

    // Function to get the number of inserted nodes
    int insertAmount() {
        return amount;
    }
};

#endif