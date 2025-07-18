#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Function prototypes
void addStudent(fstream &f);
void displayStudents(fstream &f);
void searchStudent(fstream &f, int roll);
void deleteStudent(fstream &f, int roll);

int main() {
    fstream f;
    int choice, roll;

    while (true) {
        cout << "1. Add Student\n2. Display Students\n3. Search Student\n4. Delete Student\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                f.open("StdData.txt", ios::app);
                addStudent(f);
                f.close();
                break;
            case 2:
                f.open("StdData.txt", ios::in);
                displayStudents(f);
                f.close();
                break;
            case 3:
                cout << "Enter Roll No to search: ";
                cin >> roll;
                f.open("StdData.txt", ios::in);
                searchStudent(f, roll);
                f.close();
                break;
            case 4:
                cout << "Enter Roll No to delete: ";
                cin >> roll;
                f.open("StdData.txt", ios::in);
                deleteStudent(f, roll);
                f.close();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

void addStudent(fstream &f) {
    int roll;
    string name, division, address;
    cout << "Enter Roll No: ";
    cin >> roll;
    cin.ignore(); // To ignore the newline character left by cin
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Division: ";
    getline(cin, division);
    cout << "Enter Address: ";
    getline(cin, address);
    f << roll << " " << name << " " << division << " " << address << endl;
}

void displayStudents(fstream &f) {
    string line;
    while (getline(f, line)) {
        cout << line << endl;
    }
}

void searchStudent(fstream &f, int roll) {
    string line;
    bool found = false;
    while (getline(f, line)) {
        int currentRoll;
        stringstream ss(line);
        ss >> currentRoll;
        if (currentRoll == roll) {
            cout << line << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Student with Roll No " << roll << " not found." << endl;
    }
}

void deleteStudent(fstream &f, int roll) {
    fstream temp;
    temp.open("TempData.txt", ios::out);
    if (!temp) {
        cout << "Error opening temporary file!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(f, line)) {
        int currentRoll;
        stringstream ss(line);
        ss >> currentRoll;
        if (currentRoll != roll) {
            temp << line << endl;
        } else {
            found = true;
        }
    }

    f.close();
    temp.close();

    if (found) {
        remove("StdData.txt");
        rename("TempData.txt", "StdData.txt");
        cout << "Student with Roll No " << roll << " deleted successfully." << endl;
    } else {
        remove("TempData.txt");
        cout << "Student with Roll No " << roll << " not found." << endl;
    }
}