#include <iostream>
#include <queue>
using namespace std;

// Node structure for BST
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Function to insert a node in BST
Node* insert(Node* root, int data) {
    if (root == nullptr) {
        root = createNode(data);
    } else if (data <= root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function to display the BST using inorder traversal
void display(Node* root) {
    if (root == nullptr) return;
    display(root->left);
    cout << root->data << " ";
    display(root->right);
}

// Function to delete a node from BST
Node* deleteNode(Node* root, int key) {
    if (root == nullptr) return root;
    else if (key < root->data) root->left = deleteNode(root->left, key);
    else if (key > root->data) root->right = deleteNode(root->right, key);
    else {
        // Case 1: No child or only one child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // Case 2: Node with two children
        Node* temp = root->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to calculate the depth of the tree
int depth(Node* root) {
    if (root == nullptr) return 0;
    else {
        int leftDepth = depth(root->left);
        int rightDepth = depth(root->right);
        return max(leftDepth, rightDepth) + 1;
    }
}

int main() {
    Node* root = nullptr;
    int choice, data;

    do {
        cout << "\nBinary Search Tree Operations:" << endl;
        cout << "1. Insert\n2. Display\n3. Delete\n4. Depth\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter data to insert: ";
                cin >> data;
                root = insert(root, data);
                break;
            case 2:
                cout << "BST elements: ";
                display(root);
                cout << endl;
                break;
            case 3:
                cout << "Enter data to delete: ";
                cin >> data;
                root = deleteNode(root, data);
                break;
            case 4:
                cout << "Depth of BST: " << depth(root) << endl;
                break;
            case 5:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}