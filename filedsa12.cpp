#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
void addEmployee(fstream &f, fstream &f1);
void displayEmployees(fstream &f);
void searchEmployee(fstream &f, fstream &f1, int emid);
void deleteEmployee(fstream &f, fstream &f1, int emid);
int main() {
    fstream f, f1;
    int choice, emid;
    while (true) {
        cout << "1. Add Employee Data\n2. Display Employee Data\n3. Delete Employee Data\n4. Search Employee Detail\n5. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                f.open("EmpData.txt", ios::app);
                f1.open("Index.txt", ios::app);
                addEmployee(f, f1);
                f.close();
                f1.close();
                break;
            case 2:
                f.open("EmpData.txt", ios::in);
                displayEmployees(f);
                f.close();
                break;
            case 3:
                cout << "Enter Employee ID to delete: ";
                cin >> emid;
                f.open("EmpData.txt", ios::in);
                f1.open("Index.txt", ios::in);
                deleteEmployee(f, f1, emid);
                f.close();
                f1.close();
                break;
            case 4:
                cout << "Enter Employee ID to search: ";
                cin >> emid;
                f.open("EmpData.txt", ios::in);
                f1.open("Index.txt", ios::in);
                searchEmployee(f, f1, emid);
                f.close();
                f1.close();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}
void addEmployee(fstream &f, fstream &f1) {
    int emid, salary;
    string name, position;
    cout << "Enter Employee ID: ";
    cin >> emid;
    cin.ignore(); 
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Position: ";
    getline(cin, position);
    cout << "Enter Salary: ";
    cin >> salary;
    f << emid << " " << name << " " << position << " " << salary << endl;
    f1 << emid << endl;
}
void displayEmployees(fstream &f) {
    string line;
    while (getline(f, line)) {
        cout << line << endl;
    }
}
void searchEmployee(fstream &f, fstream &f1, int emid) {
    string line;
    bool found = false;
    while (getline(f1, line)) {
        int currentEmid;
        stringstream ss(line);
        ss >> currentEmid;
        if (currentEmid == emid) {
            while (getline(f, line)) {
                stringstream ss(line);
                ss >> currentEmid;
                if (currentEmid == emid) {
                    cout << line << endl;
                    found = true;
                    break;
                }
            }
            break;
        }
    }
    if (!found) {
        cout << "Employee with ID " << emid << " not found." << endl;
    }
}
void deleteEmployee(fstream &f, fstream &f1, int emid) {
    fstream temp, tempIndex;
    temp.open("TempData.txt", ios::out);
    tempIndex.open("TempIndex.txt", ios::out);
    if (!temp || !tempIndex) {
        cout << "Error opening temporary file!" << endl;
        return;
    }
    string line;
    bool found = false;
    while (getline(f, line)) {
        int currentEmid;
        stringstream ss(line);
        ss >> currentEmid;
        if (currentEmid != emid) {
            temp << line << endl;
        } else {
            found = true;
        }
    }
    while (getline(f1, line)) {
        int currentEmid;
        stringstream ss(line);
        ss >> currentEmid;
        if (currentEmid != emid) {
            tempIndex << line << endl;
        }
    }
    f.close();
    f1.close();
    temp.close();
    tempIndex.close();
    if (found) {
        remove("EmpData.txt");
        rename("TempData.txt", "EmpData.txt");
        remove("Index.txt");
        rename("TempIndex.txt", "Index.txt");
        cout << "Employee with ID " << emid << " deleted successfully." << endl;
    } else {
        remove("TempData.txt");
        remove("TempIndex.txt");
        cout << "Employee with ID " << emid << " not found." << endl;
    }
}