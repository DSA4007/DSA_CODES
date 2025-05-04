#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class OBSTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    vector<int> keys;
    vector<float> prob;
    Node* root;

    Node* buildTree(const vector<vector<int>>& rootTable, int i, int j) {
        if (j < i) return nullptr;
        int r = rootTable[i][j];
        Node* node = new Node(keys[r]);
        node->left = buildTree(rootTable, i, r - 1);
        node->right = buildTree(rootTable, r + 1, j);
        return node;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

    void destroyTree(Node* node) {
        if (!node) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    OBSTree() : root(nullptr) {}

    void createOBST(const vector<int>& k, const vector<float>& p) {
        int n = k.size();
        keys = k;
        prob = p;

        vector<vector<float>> cost(n, vector<float>(n, 0));
        vector<vector<int>> rootTable(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            cost[i][i] = prob[i];
            rootTable[i][i] = i;
        }

        for (int L = 2; L <= n; L++) {
            for (int i = 0; i <= n - L; i++) {
                int j = i + L - 1;
                cost[i][j] = INT_MAX;
                float sumProb = 0;

                for (int s = i; s <= j; s++) sumProb += prob[s];

                for (int r = i; r <= j; r++) {
                    float c = ((r > i) ? cost[i][r - 1] : 0) +
                              ((r < j) ? cost[r + 1][j] : 0) +
                              sumProb;

                    if (c < cost[i][j]) {
                        cost[i][j] = c;
                        rootTable[i][j] = r;
                    }
                }
            }
        }

        root = buildTree(rootTable, 0, n - 1);
        cout << "Optimal BST constructed with minimal cost: " << cost[0][n - 1] << "\n";
    }

    void printInorder() {
        cout << "Inorder Traversal of OBST: ";
        inorder(root);
        cout << "\n";
    }

    ~OBSTree() {
        destroyTree(root);
    }
};

int main() {
    OBSTree tree;
    int choice;

    while (true) {
        cout << "\n--- OBST Menu ---\n";
        cout << "1. Create Optimal BST\n";
        cout << "2. Print Inorder Traversal\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int n;
            cout << "Enter number of keys: ";
            cin >> n;

            vector<int> keys(n);
            vector<float> prob(n);

            cout << "Enter " << n << " sorted keys (integers):\n";
            for (int i = 0; i < n; i++) {
                cin >> keys[i];
            }

            cout << "Enter corresponding search probabilities (as floats):\n";
            for (int i = 0; i < n; i++) {
                cin >> prob[i];
            }

            tree.createOBST(keys, prob);
        } else if (choice == 2) {
            tree.printInorder();
        } else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
