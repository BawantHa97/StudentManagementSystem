#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "admin.h"
#include "student.h"

using namespace std;

bool adminLogin(string& username, string& password) {
    const string expectedUsername = "admin";
    const string expectedPassword = "std1234";

    cout << endl << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username == expectedUsername && password == expectedPassword) {
        cout << "Login successful!" << endl;
        return true;
    } else {
        cout << "Invalid username or password!" << endl;
        return false;
    }
}

bool studentLogin(string& username, string& password){
    const string expectedUsername = "student";
    const string expectedPassword = "std2024";
    cout << endl << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username == expectedUsername && password == expectedPassword) {
        cout << "Login successful!" << endl;
        return true;
    } else {
        cout << "Invalid username or password!" << endl;
        return false;
    }
}

int main() {
        int ch;
    cout << "======================  Welcome to ABC College System  =========================="<<endl;
    cout << "Choose :"<<endl;
    cout << "1. Admin"<<endl;
    cout << "2. Student"<<endl;
    cout << "Your Choice  : ";
    cin>> ch;
     cin.ignore();

     switch(ch){
         case 1 :{
    string username, password;
    if (!adminLogin(username, password)) {
        return 1;  // Exit if login fails
    }

    Admin admin;

    // Load students from file
    ifstream file("students.txt");
    if (file) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            Student student;
            try {
                getline(ss, token, ',');
                student.setRollNumber(stoi(token));  // stoi may throw an exception
                getline(ss, token, ',');
                student.setName(token);
                getline(ss, token, ',');
                student.setAddress(token);
                getline(ss, token, ',');
                student.setContactDetails(token);
                getline(ss, token, ',');
                student.setEmail(token);
                admin.addStudent(student);
            } catch (const invalid_argument& e) {
                cerr << "Invalid data format in file: " << line << endl;
            } catch (const out_of_range& e) {
                cerr << "Number out of range in file: " << line << endl;
            }
        }
        file.close();
    }

    int choice;
    while (true) {
        cout << endl << "Admin Menu:" << endl;
        cout << "1. Add New Student" << endl;
        cout << "2. View Students" << endl;
        cout << "3. Update Student" << endl;
        cout << "4. Delete Student" << endl;
        cout << "5. Add Grades" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Clear newline character left in buffer

        switch (choice) {
            case 1: {
                Student student;
                int rollNumber;
                cout << "Enter roll number: ";
                cin >> rollNumber;
                student.setRollNumber(rollNumber);
                cin.ignore();  // Clear newline character left in buffer

                string name;
                cout << "Enter name: ";
                getline(cin, name);
                student.setName(name);

                string address;
                cout << "Enter address: ";
                getline(cin, address);
                student.setAddress(address);

                string contactDetails;
                cout << "Enter contact details: ";
                getline(cin, contactDetails);
                student.setContactDetails(contactDetails);

                string email;
                cout << "Enter email: ";
                getline(cin, email);
                student.setEmail(email);

                admin.addStudent(student);
                break;
            }
            case 2:
                admin.viewStudents();
                break;
            case 3: {
                int rollNumber;
                cout << "Enter roll number of student to update: ";
                cin >> rollNumber;
                cin.ignore();  // Clear newline character left in buffer
                admin.updateStudent(rollNumber);
                break;
            }
            case 4: {
                int rollNumber;
                cout << "Enter roll number of student to delete: ";
                cin >> rollNumber;
                admin.deleteStudent(rollNumber);
                break;
            }
            case 5: {
                int rollNumber;
                cout << "Enter roll number of student to add grades: ";
                cin >> rollNumber;
                cin.ignore();  // Clear newline character left in buffer

                string subject;
                int grade;
                cout << "Enter subject: ";
                getline(cin, subject);
                cout << "Enter grade: ";
                cin >> grade;
                cin.ignore();  // Clear newline character left in buffer

                Student* student = admin.findStudentByRollNumber(rollNumber);
                if (student) {
                    student->addGrade(subject, grade);
                    admin.saveGradesToFile();
                } else {
                    cout << "Student not found!" << endl;
                }

                break;
            }
            case 6:
                admin.saveStudentsToFile();
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
         case 2 : {
             string username, password;
            if (!studentLogin(username, password)) {
                return 1;  // Exit if login fails
            }

            Student student;

            cout << "Enter your Roll Number: ";
            int rollNumber;
            cin >> rollNumber;
            cin.ignore();

            // Load student data from file
            ifstream file("students.txt");
            if (file) {
                string line;
                while (getline(file, line)) {
                    stringstream ss(line);
                    string token;
                    try {
                        getline(ss, token, ',');
                        int currentRollNumber = stoi(token);  // stoi may throw an exception
                        if (currentRollNumber == rollNumber) {
                            student.setRollNumber(currentRollNumber);
                            getline(ss, token, ',');
                            student.setName(token);
                            getline(ss, token, ',');
                            student.setAddress(token);
                            getline(ss, token, ',');
                            student.setContactDetails(token);
                            getline(ss, token, ',');
                            student.setEmail(token);
                            break;
                        }
                    } catch (const invalid_argument& e) {
                        cerr << "Invalid data format in file: " << line << endl;
                    } catch (const out_of_range& e) {
                        cerr << "Number out of range in file: " << line << endl;
                    }
                }
                file.close();
            }

            // Load grades from file
            ifstream gradesFile("grades.txt");
            if (gradesFile) {
                string line;
                while (getline(gradesFile, line)) {
                    stringstream ss(line);
                    string token;
                    getline(ss, token, ',');
                    int currentRollNumber = stoi(token);  // stoi may throw an exception
                    if (currentRollNumber == rollNumber) {
                        string subject;
                        int grade;
                        getline(ss, token, ',');
                        subject = token;
                        getline(ss, token, ',');
                        grade = stoi(token);  // stoi may throw an exception
                        student.addGrade(subject, grade);
                    }
                }
                gradesFile.close();
            }

            int choice;
            while (true) {
                cout <<endl << "Student Menu:" << endl;
                cout << "1. View Profile" << endl;
                cout << "2. View Grades" << endl;
                cout << "3. Logout" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();  // Clear newline character left in buffer

                switch (choice) {
                    case 1:
                        student.viewProfile();
                        break;
                    case 2:
                        student.viewGrades();
                        break;
                    case 3:
                        return 0;
                    default:
                        cout << "Invalid choice!" << endl;
                }
            }

            return 0;
        }
        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }
}
