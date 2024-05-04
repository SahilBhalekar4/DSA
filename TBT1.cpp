#include <iostream>
#include <stack>

// Node structure for threaded binary tree
struct Node {
    int data;
    Node* left;
    Node* right;
    bool isThreaded; // Indicates if right pointer is a thread or not
};

// Function to create a new node
Node* newNode(int data) {
    Node* node = new Node();
    node->data = data;
    node->left = node->right = nullptr;
    node->isThreaded = false;
    return node;
}

// Function to insert a node in the threaded binary tree
Node* insert(Node* root, int data) {
    if (root == nullptr)
        return newNode(data);

    Node* temp = root;
    Node* prev = nullptr;
    while (temp != nullptr) {
        prev = temp;
        if (data < temp->data) {
            if (temp->left == nullptr) {
                temp->left = newNode(data);
                temp->left->right = temp;
                temp->left->isThreaded = true;
                return root;
            }
            temp = temp->left;
        } else {
            if (temp->right == nullptr || !temp->isThreaded) {
                Node* newNodePtr = newNode(data);
                newNodePtr->right = temp->right;
                temp->right = newNodePtr;
                temp->isThreaded = false;
                newNodePtr->isThreaded = true;
                return root;
            }
            temp = temp->right;
        }
    }

    prev->right = newNode(data);
    prev->isThreaded = false;
    return root;
}

// Function to perform in-order traversal using threaded binary tree
void inOrder(Node* root) {
    Node* curr = root;
    while (curr != nullptr) {
        if (curr->left == nullptr) {
            std::cout << curr->data << " ";
            curr = curr->right;
        } else {
            // Find predecessor
            Node* pre = curr->left;
            while (pre->right != nullptr && pre->right != curr)
                pre = pre->right;

            // Make current as right child of its inorder predecessor
            if (pre->right == nullptr) {
                pre->right = curr;
                curr = curr->left;
            } else {
                // Restore original tree
                pre->right = nullptr;
                std::cout << curr->data << " ";
                curr = curr->right;
            }
        }
    }
}

// Function to perform pre-order traversal using threaded binary tree
void preOrder(Node* root) {
    while (root != nullptr) {
        std::cout << root->data << " ";
        if (root->left != nullptr)
            root = root->left;
        else if (root->right != nullptr && root->isThreaded)
            root = root->right;
        else {
            while (root != nullptr && !root->isThreaded)
                root = root->right;
            if (root != nullptr)
                root = root->right;
        }
    }
}

int main() {
    Node* root = nullptr;
    char choice;
    int data;

    do {
        std::cout << "Enter data to insert: ";
        std::cin >> data;
        root = insert(root, data);

        std::cout << "Do you want to insert another node? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    std::cout << "\nInorder traversal: ";
    inOrder(root);
    std::cout << std::endl;

    std::cout << "Preorder traversal: ";
    preOrder(root);
    std::cout << std::endl;

    return 0;
}
