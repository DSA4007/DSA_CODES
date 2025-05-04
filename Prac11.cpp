#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Student {
public:
    int roll;
    string name;
    string division;
    string address;

    void input() {
        cout << "Enter roll number: ";
        cin >> roll;
        cin.ignore(); // Flush newline

        cout << "Enter name: ";
        getline(cin, name);

        cout << "Enter division: ";
        getline(cin, division);

        cout << "Enter address: ";
        getline(cin, address);
    }

    void display() const {
        cout << "Roll Number: " << roll << "\n";
        cout << "Name: " << name << "\n";
        cout << "Division: " << division << "\n";
        cout << "Address: " << address << "\n";
    }
};

void addStudent() {
    ofstream file("students.txt", ios::app);
    if (!file) {
        cerr << "Error opening file.\n";
        return;
    }

    Student s;
    s.input();
    file << s.roll << "," << s.name << "," << s.division << "," << s.address << "\n";
    file.close();
    cout << "Student added successfully.\n";
}

void displayStudent(int searchRoll) {
    ifstream file("students.txt");
    if (!file) {
        cerr << "Error opening file.\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        int roll;
        string name, division, address;

        size_t p1 = line.find(',');
        size_t p2 = line.find(',', p1 + 1);
        size_t p3 = line.find(',', p2 + 1);

        roll = stoi(line.substr(0, p1));
        name = line.substr(p1 + 1, p2 - p1 - 1);
        division = line.substr(p2 + 1, p3 - p2 - 1);
        address = line.substr(p3 + 1);

        if (roll == searchRoll) {
            Student s{roll, name, division, address};
            s.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student record not found.\n";
    }

    file.close();
}

void deleteStudent(int deleteRoll) {
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file || !temp) {
        cerr << "Error opening file.\n";
        return;
    }

    string line;
    bool deleted = false;

    while (getline(file, line)) {
        int roll = stoi(line.substr(0, line.find(',')));
        if (roll != deleteRoll) {
            temp << line << "\n";
        } else {
            deleted = true;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (deleted) {
        cout << "Student deleted successfully.\n";
    } else {
        cout << "Student not found.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n--- Student Management Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student Info\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2: {
                int roll;
                cout << "Enter roll number to delete: ";
                cin >> roll;
                deleteStudent(roll);
                break;
            }
            case 3: {
                int roll;
                cout << "Enter roll number to display: ";
                cin >> roll;
                displayStudent(roll);
                break;
            }
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
