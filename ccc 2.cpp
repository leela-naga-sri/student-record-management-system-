#include <iostream>
#include <string>
using namespace std;

class Student {   
public:
    int roll;
    string name;   
    float marks;
    Student* prev;
    Student* next;

    Student(int r, string n, float m) {
        roll = r;
        name = n;
        marks = m;
        prev = NULL;
        next = NULL;
    }
};

Student* head = NULL;

int getValidInt(string msg) {
    int x;
    cout << msg;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! " << msg;
    }
    return x;
}

float getValidFloat(string msg) {
    float x;
    cout << msg;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! " << msg;
    }
    return x;
}

void addStudent() {
    int roll = getValidInt("\nEnter Roll No (<=60): ");

    if (roll > 60) {
        cout << "Roll number should be <= 60!\n";
        return;
    }

    cin.ignore();
    string name;
    cout << "Enter Name: ";
    getline(cin, name);

    float marks = getValidFloat("Enter Marks: ");

    Student* newStudent = new Student(roll, name, marks);

    if (head == NULL) {
        head = newStudent;
    } else {
        Student* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newStudent;
        newStudent->prev = temp;
    }

    cout << "Student added successfully!\n";
}

void displayStudents() {
    if (head == NULL) {
        cout << "\nNo records to display.\n";
        return;
    }

    Student* temp = head;
    cout << "\n--- Student Records ---\n";
    while (temp != NULL) {
        cout << "Roll: " << temp->roll
            << ", Name: " << temp->name
            << ", Marks: " << temp->marks << endl;
        temp = temp->next;
    }
}

Student* searchStudent(int roll) {
    Student* temp = head;
    while (temp != NULL) {
        if (temp->roll == roll)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void updateStudent() {
    int roll = getValidInt("\nEnter roll number to update: ");

    Student* s = searchStudent(roll);
    if (s == NULL) {
        cout << "Student not found!\n";
        return;
    }

    cin.ignore();
    cout << "Enter new name: ";
    getline(cin, s->name);

    s->marks = getValidFloat("Enter new marks: ");

    cout << "Record updated successfully!\n";
}

void deleteStudent() {
    int roll = getValidInt("\nEnter roll number to delete: ");

    Student* s = searchStudent(roll);
    if (s == NULL) {
        cout << "Student not found!\n";
        return;
    }

    if (s->prev != NULL)
        s->prev->next = s->next;
    else
        head = s->next;

    if (s->next != NULL)
        s->next->prev = s->prev;

    delete s;
    cout << "Record deleted successfully!\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== Student Record Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Student Records\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";

        choice = getValidInt("Enter your choice: ");

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3: {
            int roll = getValidInt("Enter roll number to search: ");
            Student* s = searchStudent(roll);
            if (s)
                cout << "Found -> Roll: " << s->roll << ", Name: " << s->name << ", Marks: " << s->marks << endl;
            else
                cout << "Student not found.\n";
            break;
        }
        case 4:
            updateStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}

