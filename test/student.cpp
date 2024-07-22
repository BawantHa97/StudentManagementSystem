#include "student.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

Student::Student(int rollNumber, const string& name, const string& address, const string& contactDetails, const string& email)
    : rollNumber(rollNumber), name(name), address(address), contactDetails(contactDetails), email(email) {}

int Student::getRollNumber() const {
    return rollNumber;
}

string Student::getName() const {
    return name;
}

string Student::getAddress() const {
    return address;
}

string Student::getContactDetails() const {
    return contactDetails;
}

string Student::getEmail() const {
    return email;
}

map<string, int> Student::getGrades() const {
    return grades;
}

void Student::setRollNumber(int rollNumber) {
    this->rollNumber = rollNumber;
}

void Student::setName(const string& name) {
    this->name = name;
}

void Student::setAddress(const string& address) {
    this->address = address;
}

void Student::setContactDetails(const string& contactDetails) {
    this->contactDetails = contactDetails;
}

void Student::setEmail(const string& email) {
    this->email = email;
}

void Student::addGrade(const string& subject, int grade) {
    grades[subject] = grade;
}

Student Student::loadFromFile(ifstream& file) {
    string line;
    if (getline(file, line)) {
        stringstream ss(line);
        string token;
        int rollNumber;
        string name, address, contactDetails, email;

        getline(ss, token, ',');
        rollNumber = stoi(token);

        getline(ss, token, ',');
        name = token;

        getline(ss, token, ',');
        address = token;

        getline(ss, token, ',');
        contactDetails = token;

        getline(ss, token, ',');
        email = token;

        return Student(rollNumber, name, address, contactDetails, email);
    }
    throw runtime_error("Failed to load student from file");
}
void Student::viewProfile() const {
    cout << endl << "Profile Information:" << endl;
    cout << "Roll Number: " << rollNumber << endl;
    cout << "Name: " << name << endl;
    cout << "Address: " << address << endl;
    cout << "Contact Details: " << contactDetails << endl;
    cout << "Email: " << email << endl<<endl;
}

void Student::viewGrades() const {
    cout << endl << "Grades:" << endl;
    int total = 0;
    for (const auto& grade : grades) {
        cout << "Subject: " << grade.first << " -   Grade: " << grade.second << endl;
        total += grade.second;
    }
    double average = grades.empty() ? 0 : static_cast<double>(total) / grades.size();
    cout << "Total  : " << total << endl;
    cout << "Average  : " << average << endl<<endl;
}

string Student::toCSV() const {
    stringstream ss;
    ss << rollNumber << "," << name << "," << address << "," << contactDetails << "," << email;
    return ss.str();
}
string Student::gradesToCSV() const {
    stringstream ss;
    for (const auto& grade : grades) {
        ss << rollNumber << "," << grade.first << "," << grade.second << endl;
    }
    return ss.str();
}
