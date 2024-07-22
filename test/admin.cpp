#include "admin.h"
#include "student.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void Admin::addStudent(const Student& student) {
    students.push_back(student);
}

void Admin::viewStudents() {
    for (const Student& student : students) {
        cout << endl << "Roll Number: " << student.getRollNumber() << endl;
        cout << "Name: " << student.getName() << endl;
        cout << "Address: " << student.getAddress() << endl;
        cout << "Contact Details: " << student.getContactDetails() << endl;
        cout << "Email : " << student.getEmail() <<endl;
    }
}

void Admin::updateStudent(int rollNumber) {
    for (auto& student : students) {
        if (student.getRollNumber() == rollNumber) {
            string name, address, contactDetails,email;
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, name);
            student.setName(name);
            cout << "Enter new address: ";
            getline(cin, address);
            student.setAddress(address);
            cout << "Enter new contact details: ";
            getline(cin, contactDetails);
            student.setContactDetails(contactDetails);
            cout << "Enter the new email : ";
            getline(cin,email);
            student.setEmail(email);
            return;
        }
    }

    cout << "Student not found." << endl;
}

void Admin::deleteStudent(int rollNumber) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getRollNumber() == rollNumber) {
            students.erase(it);
            return;
        }
    }

    cout << "Student not found." << endl;
}

void Admin::addGrades(int rollNumber) {
    Student* student = findStudentByRollNumber(rollNumber);
    if (student) {
        string subject;
        int grade;
        cout << "Enter subject: ";
        cin >> subject;
        cout << "Enter grade: ";
        cin >> grade;
        student->addGrade(subject, grade);
    } else {
        cout << "Student not found!" << endl;
    }
    }

void Admin::saveStudentsToFile() {
    ofstream file("students.txt");
    if (file.is_open()) {
        for (const Student& student : students) {
            file << student.toCSV() << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}
void Admin::saveGradesToFile() const {
    ofstream file("grades.txt", ios::app);
    if (file) {
        for (const Student& student : students) {
            for (const auto& grade : student.getGrades()) {
                file << student.getRollNumber() << "," << grade.first << "," << grade.second << endl;
            }
        }
        file.close();
    } else {
        cerr << "Unable to open file for writing." << endl;
    }
}
Student* Admin::findStudentByRollNumber(int rollNumber) {
    for (auto& student : students) {
        if (student.getRollNumber() == rollNumber) {
            return &student;
        }
    }
    return nullptr;
}
