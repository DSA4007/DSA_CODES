#include<iostream>
#include<string>

using namespace std;

class node {
public:
    string key, meaning;
    node *left, *right;
    
    node() : left(nullptr), right(nullptr) {} // Constructor to initialize left and right pointers to nullptr
};

class AVL {
    node* root;

public:
    AVL() : root(nullptr) {} // Constructor to initialize root to nullptr

    ~AVL() { destroyTree(root); } // Destructor to deallocate memory

    void destroyTree(node* cur) {
        if (cur != nullptr) {
            destroyTree(cur->left);
            destroyTree(cur->right);
            delete cur; // Deallocate memory for the current node
        }
    }

    void create() {
        char answer;
        do {
            node* temp = new node(); // Dynamically create a new node
            cout << "\nEnter the keyword: ";
            cin >> temp->key;
            cout << "Enter the meaning: ";
            cin >> temp->meaning;
            temp->left = temp->right = nullptr; // Initialize left and right pointers to null

            root = insert(root, temp); // Insert the node into the tree
            cout << "Do you want to add another word? (y/n): ";
            cin >> answer;
        } while (answer == 'y' || answer == 'Y');
    }

    node* insert(node* cur, node* temp) {
        if (cur == nullptr) {
            return temp; // If the current node is null, return the new node
        }

        if (temp->key < cur->key) {
            cur->left = insert(cur->left, temp); // Insert in the left subtree
        } else if (temp->key > cur->key) {
            cur->right = insert(cur->right, temp); // Insert in the right subtree
        }

        return balance(cur); // Balance the tree after insertion
    }

    node* balance(node* cur) {
        int balanceFactor = height(cur->left) - height(cur->right);
        
        if (balanceFactor > 1) {
            if (height(cur->left->left) >= height(cur->left->right)) {
                cur = LL(cur); // Left-Left Case
            } else {
                cur = LR(cur); // Left-Right Case
            }
        } else if (balanceFactor < -1) {
            if (height(cur->right->right) >= height(cur->right->left)) {
                cur = RR(cur); // Right-Right Case
            } else {
                cur = RL(cur); // Right-Left Case
            }
        }

        return cur; // Return the balanced node
    }

    int height(node* temp) {
        if (temp == nullptr) {
            return 0;
        }
        return max(height(temp->left), height(temp->right)) + 1;
    }

    node* LL(node* par) {
        node* temp = par->left;
        par->left = temp->right;
        temp->right = par;
        return temp;
    }

    node* RR(node* par) {
        node* temp = par->right;
        par->right = temp->left;
        temp->left = par;
        return temp;
    }

    node* LR(node* par) {
        par->left = RR(par->left);
        return LL(par);
    }

    node* RL(node* par) {
        par->right = LL(par->right);
        return RR(par);
    }

    void ascending(node* temp) {
        if (temp != nullptr) {
            ascending(temp->left); // Traverse left subtree
            cout << "\n\t" << temp->key << ": " << temp->meaning;
            ascending(temp->right); // Traverse right subtree
        }
    }

    void descending(node* temp) {
        if (temp != nullptr) {
            descending(temp->right); // Traverse right subtree
            cout << "\n\t" << temp->key << ": " << temp->meaning;
            descending(temp->left); // Traverse left subtree
        }
    }

    void display() {
        cout << "\nThe keywords in ascending order are:";
        ascending(root);
        cout << "\nThe keywords in descending order are:";
        descending(root);
        cout << "\n";
    }

    bool search(node* cur, string key) {
        if (cur == nullptr) {
            return false; // Return false if the tree is empty or the key is not found
        }

        if (cur->key == key) {
            return true; // Return true if the key matches
        } else if (key < cur->key) {
            return search(cur->left, key); // Search in the left subtree
        } else {
            return search(cur->right, key); // Search in the right subtree
        }
    }

    void search_value() {
        string key;
        cout << "\nEnter the keyword you wish to search: ";
        cin >> key;

        if (search(root, key)) {
            cout << "\nThe entered keyword is present in the AVL tree.";
        } else {
            cout << "\nThe entered keyword is not present in the AVL tree.";
        }
        cout << "\n";
    }

    node* delete_n(node* cur, string key) {
        if (cur == nullptr) {
            return nullptr; // If the node is not found, return null
        }

        if (key < cur->key) {
            cur->left = delete_n(cur->left, key); // Search in the left subtree
        } else if (key > cur->key) {
            cur->right = delete_n(cur->right, key); // Search in the right subtree
        } else {
            if (cur->left == nullptr) {
                node* temp = cur->right; // Node has only right child
                delete cur;
                return temp;
            } else if (cur->right == nullptr) {
                node* temp = cur->left; // Node has only left child
                delete cur;
                return temp;
            }

            node* temp = extractmin(cur->right); // Node has two children
            cur->key = temp->key;
            cur->meaning = temp->meaning;
            cur->right = delete_n(cur->right, temp->key); // Delete the successor
        }

        return balance(cur); // Balance the tree after deletion
    }

    node* extractmin(node* t) {
        if (t->left == nullptr) {
            return t;
        }
        return extractmin(t->left); // Traverse to the leftmost node
    }

    void deleten() {
        string key;
        cout << "\nEnter the keyword to be deleted: ";
        cin >> key;
        root = delete_n(root, key); // Delete the keyword from the tree
    }
};

int main() {
    char c;
    int ch;
    AVL a;

    do {
        cout << "******\n";
        cout << "\n1. Insert a keyword in AVL tree.";
        cout << "\n2. Display the AVL tree.";
        cout << "\n3. Search a keyword.";
        cout << "\n4. Delete a keyword.";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1: a.create(); break;
        case 2: a.display(); break;
        case 3: a.search_value(); break;
        case 4: a.deleten(); break;
        default: cout << "\nWrong choice!";
        }

        cout << "\nDo you want to continue? (y/n): ";
        cin >> c;
    } while (c == 'y' || c == 'Y');

    return 0;
}
