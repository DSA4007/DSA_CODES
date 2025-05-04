#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Student {
public:
    int roll;
    std::string name;
    std::string division;
    std::string address;

    void input() {
        std::cout << "Enter roll number: ";
        std::cin >> roll;
        std::cin.ignore(); // Flush newline

        std::cout << "Enter name: ";
        std::getline(std::cin, name);

        std::cout << "Enter division: ";
        std::getline(std::cin, division);

        std::cout << "Enter address: ";
        std::getline(std::cin, address);
    }

    void display() const {
        std::cout << "Roll Number: " << roll << "\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "Division: " << division << "\n";
        std::cout << "Address: " << address << "\n";
    }
};

void addStudent() {
    std::ofstream file("students.txt", std::ios::app);
    if (!file) {
        std::cerr << "Error opening file.\n";
        return;
    }

    Student s;
    s.input();
    file << s.roll << "," << s.name << "," << s.division << "," << s.address << "\n";
    file.close();
    std::cout << "Student added successfully.\n";
}

void displayStudent(int searchRoll) {
    std::ifstream file("students.txt");
    if (!file) {
        std::cerr << "Error opening file.\n";
        return;
    }

    std::string line;
    bool found = false;

    while (std::getline(file, line)) {
        int roll;
        std::string name, division, address;

        size_t p1 = line.find(',');
        size_t p2 = line.find(',', p1 + 1);
        size_t p3 = line.find(',', p2 + 1);

        roll = std::stoi(line.substr(0, p1));
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
        std::cout << "Student record not found.\n";
    }

    file.close();
}

void deleteStudent(int deleteRoll) {
    std::ifstream file("students.txt");
    std::ofstream temp("temp.txt");

    if (!file || !temp) {
        std::cerr << "Error opening file.\n";
        return;
    }

    std::string line;
    bool deleted = false;

    while (std::getline(file, line)) {
        int roll = std::stoi(line.substr(0, line.find(',')));
        if (roll != deleteRoll) {
            temp << line << "\n";
        } else {
            deleted = true;
        }
    }

    file.close();
    temp.close();

    std::remove("students.txt");
    std::rename("temp.txt", "students.txt");

    if (deleted) {
        std::cout << "Student deleted successfully.\n";
    } else {
        std::cout << "Student not found.\n";
    }
}

int main() {
    int choice;
    do {
        std::cout << "\n--- Student Management Menu ---\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. Delete Student\n";
        std::cout << "3. Display Student Info\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2: {
                int roll;
                std::cout << "Enter roll number to delete: ";
                std::cin >> roll;
                deleteStudent(roll);
                break;
            }
            case 3: {
                int roll;
                std::cout << "Enter roll number to display: ";
                std::cin >> roll;
                displayStudent(roll);
                break;
            }
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
