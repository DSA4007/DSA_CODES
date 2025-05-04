#include<iostream>
#include<cstdlib>
using namespace std;

class node {
public:
    int info;
    node* left;
    node* right;
};

class BST {
public:
    node* root;
    BST() {
        root = NULL;
    }
    void insert(node*, node*);
    void display(node*, int);
    int min(node*);
    int height(node*);
    void mirror(node*);
    void preorder(node*);
    void inorder(node*);
    void postorder(node*);
    void search(node*, int);
};

void BST::insert(node* tree, node* newnode) {
    if (root == NULL) {
        root = newnode;
        root->left = root->right = NULL;
        cout << "Root node added.\n";
        return;
    }

    if (tree->info == newnode->info) {
        cout << "Element already exists.\n";
        return;
    }

    if (newnode->info < tree->info) {
        if (tree->left != NULL)
            insert(tree->left, newnode);
        else {
            tree->left = newnode;
            newnode->left = newnode->right = NULL;
            cout << "Node added to the left.\n";
        }
    } else {
        if (tree->right != NULL)
            insert(tree->right, newnode);
        else {
            tree->right = newnode;
            newnode->left = newnode->right = NULL;
            cout << "Node added to the right.\n";
        }
    }
}

void BST::display(node* ptr, int level) {
    if (ptr != NULL) {
        display(ptr->right, level + 1);
        cout << endl;
        for (int i = 0; i < level; i++)
            cout << "   ";
        cout << ptr->info;
        display(ptr->left, level + 1);
    }
}

int BST::min(node* root) {
    if (root == NULL) {
        cout << "Tree is empty.\n";
        return -1;
    }
    node* temp = root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp->info;
}

int BST::height(node* root) {
    if (root == NULL)
        return 0;
    int left = height(root->left);
    int right = height(root->right);
    return max(left, right) + 1;
}

void BST::preorder(node* ptr) {
    if (ptr != NULL) {
        cout << ptr->info << " ";
        preorder(ptr->left);
        preorder(ptr->right);
    }
}

void BST::inorder(node* ptr) {
    if (ptr != NULL) {
        inorder(ptr->left);
        cout << ptr->info << " ";
        inorder(ptr->right);
    }
}

void BST::postorder(node* ptr) {
    if (ptr != NULL) {
        postorder(ptr->left);
        postorder(ptr->right);
        cout << ptr->info << " ";
    }
}

void BST::mirror(node* root) {
    if (root != NULL) {
        mirror(root->left);
        mirror(root->right);
        swap(root->left, root->right);
    }
}

void BST::search(node* ptr, int searchdata) {
    if (ptr == NULL) {
        cout << "Element not found.\n";
        return;
    }
    if (ptr->info == searchdata) {
        cout << "Element found.\n";
        return;
    }
    if (searchdata < ptr->info)
        search(ptr->left, searchdata);
    else
        search(ptr->right, searchdata);
}

int main() {
    int choice, num;
    node* temp;
    BST bst;

    while (true) {
        cout << "\n------------------------------\n";
        cout << "Operations on BST\n";
        cout << "1. Insert Element\n";
        cout << "2. Display Tree\n";
        cout << "3. Minimum Element\n";
        cout << "4. Height of Tree\n";
        cout << "5. Mirror Tree\n";
        cout << "6. Preorder Traversal\n";
        cout << "7. Inorder Traversal\n";
        cout << "8. Postorder Traversal\n";
        cout << "9. Longest Path (Number of Nodes)\n";
        cout << "10. Search Element\n";
        cout << "11. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            temp = new node();
            cout << "Enter element to insert: ";
            cin >> temp->info;
            bst.insert(bst.root, temp);
            break;
        case 2:
            cout << "BST Display:\n";
            bst.display(bst.root, 1);
            cout << endl;
            break;
        case 3:
            cout << "Minimum element: " << bst.min(bst.root) << endl;
            break;
        case 4:
            cout << "Height of tree: " << bst.height(bst.root) << endl;
            break;
        case 5:
            cout << "Mirror image of tree:\n";
            bst.mirror(bst.root);
            bst.display(bst.root, 1);
            cout << endl;
            break;
        case 6:
            cout << "Preorder Traversal: ";
            bst.preorder(bst.root);
            cout << endl;
            break;
        case 7:
            cout << "Inorder Traversal: ";
            bst.inorder(bst.root);
            cout << endl;
            break;
        case 8:
            cout << "Postorder Traversal: ";
            bst.postorder(bst.root);
            cout << endl;
            break;
        case 9:
            cout << "Number of nodes in longest path: " << bst.height(bst.root) << endl;
            break;
        case 10:
            int searchdata;
            cout << "Enter element to search: ";
            cin >> searchdata;
            bst.search(bst.root, searchdata);
            break;
        case 11:
            exit(0);
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
