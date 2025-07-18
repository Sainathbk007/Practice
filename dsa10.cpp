#include <iostream> 
#include <string>
using namespace std;
struct patient {
    int ID;
    string priority;
    string name;
};
struct patient H[100];
int size1 = -1;
int parent(int i) {
    return (i - 1) / 2;
}
int leftchild(int i) {
    return (2 * i) + 1;
}
int rightchild(int i) {
    return (2 * i) + 2;
}
void swap(struct patient& p1, struct patient& p2) {
    struct patient temp = p1;
    p1 = p2;
    p2 = temp;
}
void shiftUp(int i) {
    while (i > 0 && H[parent(i)].priority < H[i].priority) {
        swap(H[parent(i)], H[i]);
        i = parent(i);
    }
}
void shiftDown(int i) {
    int maxindex = i;
    int l = leftchild(i);
    if (l <= size1 && H[l].priority > H[maxindex].priority)  {
        maxindex = l;
    }
    int r = rightchild(i);
    if (r <= size1 && H[r].priority > H[maxindex].priority)  {
        maxindex = r;
    }
    if (i != maxindex)  {
        swap(H[i], H[maxindex]);
        shiftDown(maxindex);
    }
}
void insert(struct patient p) {
    size1 += 1;
    H[size1] = p;
    shiftUp(size1);
}
void deleteData() {
    if (size1 == -1) {
        cout << "No patients to delete!" << endl;
        return;
    }
    cout << "Serving patient with ID: " << H[0].ID << " and Name: " << H[0].name << endl;
    H[0] = H[size1];
    size1--;
    shiftDown(0);
}
void getdata() {
    int n;
    cout << "How many patient details you want to Add: ";
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        cout << "Enter patient details: " << endl;
        cout << "Patient " << i + 1 << endl;
        cout << "Enter a Patient ID: ";
        cin >> H[i].ID;
        cout << "Enter a Patient Priority (Serious (S/s), Non-serious (N/n), General Checkup (G/g)): ";
        cin >> H[i].priority;
        cin.ignore();
        cout << "Enter a Patient Name: ";
        getline(cin, H[i].name);
        insert(H[i]);
    }
}
void displaydata() {
    if (size1 == -1) {
        cout << "No patient data available!" << endl;
        return;
    }
    string priority;
    for (int i = 0; i <= size1; i++) {
        if (H[i].priority == "S" || "s") {
            priority = "Serious";
        }
        else if (H[i].priority == "N" || "n") {
            priority = "Non-serious";
        }
        else {
            priority = "General Checkup";
        }
        cout << "Patient ID: " << H[i].ID << "  Name: " << H[i].name << "  Priority: " << priority << endl;
    }
}
int main() {
    int ch;
    cout << "Menu:";
    cout << "\n1. Add Details of Patients\n2. Display Detail of Patients\n3. Serve Patient\n4. Exit";
    while (true) {
        cout << "\nEnter a choice from Menu: ";
        cin >> ch;
        if (ch == 1) {
            getdata();
        } 
        else if (ch == 2) {
            displaydata();
        } 
        else if (ch == 3) {
            deleteData();
        } 
        else if (ch == 4) {
            cout << "You are exiting....";
            break;
        } 
        else {
            cout << "Enter a valid choice....";
      	 }
    }
    return 0;
}