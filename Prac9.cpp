#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Dictionary {
private:
    struct Node {
        string keyword;
        string meaning;
        int height;
        Node* left;
        Node* right;

        Node(string k, string m) : keyword(k), meaning(m), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* node) {
        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left); // LR
            return rotateRight(node); // LL
        }
        else if (bf < -1) {
            if (balanceFactor(node->right) > 0)
                node->right = rotateRight(node->right); // RL
            return rotateLeft(node); // RR
        }

        return node;
    }

    Node* insert(Node* node, string key, string meaning) {
        if (!node)
            return new Node(key, meaning);

        if (key < node->keyword)
            node->left = insert(node->left, key, meaning);
        else if (key > node->keyword)
            node->right = insert(node->right, key, meaning);
        else {
            cout << "Keyword already exists. Use update.\n";
            return node;
        }

        return balance(node);
    }

    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, string key) {
        if (!node) return nullptr;

        if (key < node->keyword)
            node->left = remove(node->left, key);
        else if (key > node->keyword)
            node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }

            Node* successor = findMin(node->right);
            node->keyword = successor->keyword;
            node->meaning = successor->meaning;
            node->right = remove(node->right, successor->keyword);
        }

        return balance(node);
    }

    Node* update(Node* node, string key, string newMeaning) {
        if (!node) return nullptr;

        if (key < node->keyword)
            node->left = update(node->left, key, newMeaning);
        else if (key > node->keyword)
            node->right = update(node->right, key, newMeaning);
        else
            node->meaning = newMeaning;

        return node;
    }

    void displayAscending(Node* node) {
        if (!node) return;
        displayAscending(node->left);
        cout << node->keyword << ": " << node->meaning << "\n";
        displayAscending(node->right);
    }

    void displayDescending(Node* node) {
        if (!node) return;
        displayDescending(node->right);
        cout << node->keyword << ": " << node->meaning << "\n";
        displayDescending(node->left);
    }

    int getHeight(Node* node) {
        return height(node);
    }

    void destroyTree(Node* node) {
        if (!node) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    Dictionary() : root(nullptr) {}

    ~Dictionary() {
        destroyTree(root);
    }

    void add(string key, string meaning) {
        root = insert(root, key, meaning);
    }

    void deleteKeyword(string key) {
        root = remove(root, key);
    }

    void updateMeaning(string key, string newMeaning) {
        root = update(root, key, newMeaning);
    }

    void display(bool ascending = true) {
        if (ascending)
            displayAscending(root);
        else
            displayDescending(root);
    }

    int maxComparisons() {
        return getHeight(root);
    }
};

int main() {
    Dictionary dict;
    int choice;
    string key, meaning;

    while (true) {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Add Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Meaning\n";
        cout << "4. Display Ascending\n";
        cout << "5. Display Descending\n";
        cout << "6. Max Comparisons for Search\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter keyword: ";
            getline(cin, key);
            cout << "Enter meaning: ";
            getline(cin, meaning);
            dict.add(key, meaning);
            break;
        case 2:
            cout << "Enter keyword to delete: ";
            getline(cin, key);
            dict.deleteKeyword(key);
            break;
        case 3:
            cout << "Enter keyword to update: ";
            getline(cin, key);
            cout << "Enter new meaning: ";
            getline(cin, meaning);
            dict.updateMeaning(key, meaning);
            break;
        case 4:
            cout << "Dictionary (Ascending Order):\n";
            dict.display(true);
            break;
        case 5:
            cout << "Dictionary (Descending Order):\n";
            dict.display(false);
            break;
        case 6:
            cout << "Maximum comparisons for search: " << dict.maxComparisons() << "\n";
            break;
        case 7:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
