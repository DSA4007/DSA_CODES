#include <iostream>
#include <string>
using namespace std;

struct node {
    int key;
    string data;
    node* next;
};

class Dictionary {
    node* arr[10];  // Hash table

    int hash(int key) {
        return key % 10;
    }

public:
    Dictionary() {
        for (int i = 0; i < 10; i++) {
            arr[i] = nullptr;
        }
    }

    void insert(int key, const string& data);
    void display();
    void search(int key);
    void remove(int key);
};

void Dictionary::insert(int key, const string& data) {
    int index = hash(key);
    node* temp = arr[index];

    while (temp != nullptr) {
        if (temp->key == key) {
            cout << "Duplicate key found. Updating value." << endl;
            temp->data = data;
            return;
        }
        temp = temp->next;
    }

    node* newNode = new node;
    newNode->key = key;
    newNode->data = data;
    newNode->next = arr[index];
    arr[index] = newNode;
}

void Dictionary::display() {
    for (int i = 0; i < 10; i++) {
        node* p = arr[i];
        cout << i << ": ";
        while (p != nullptr) {
            cout << p->key << ":" << p->data << " --> ";
            p = p->next;
        }
        cout << "NULL" << endl;
    }
}

void Dictionary::search(int key) {
    int index = hash(key);
    node* p = arr[index];

    while (p != nullptr) {
        if (p->key == key) {
            cout << "Found: " << p->key << " => " << p->data << endl;
            return;
        }
        p = p->next;
    }
    cout << "NOT FOUND" << endl;
}

void Dictionary::remove(int key) {
    int index = hash(key);
    node* curr = arr[index];
    node* prev = nullptr;

    while (curr != nullptr) {
        if (curr->key == key) {
            if (prev == nullptr) {
                arr[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            cout << "DELETED" << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Key not found." << endl;
}

int main() {
    Dictionary dict;
    int key;
    string val;
    char choice;

    do {
        cout << "Enter key: ";
        cin >> key;
        cin.ignore(); // Ignore leftover newline from cin
        cout << "Enter value (you can include spaces): ";
        getline(cin, val);

        dict.insert(key, val);

        cout << "Press 'y' to insert more: ";
        cin >> choice;
        cin.ignore(); // Ignore newline again for safety
    } while (choice == 'y');

    cout << "\nCurrent Dictionary:\n";
    dict.display();

    cout << "\nEnter key to search: ";
    cin >> key;
    dict.search(key);

    cout << "\nEnter key to delete: ";
    cin >> key;
    dict.remove(key);

    cout << "\nFinal Dictionary:\n";
    dict.display();

    return 0;
}
