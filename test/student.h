#ifndef STUDENT_H
#define STUDENT_H
#include <vector>
#include <string>
#include <map>
using namespace std;

class Student {
private:
    int rollNumber;
    string name;
    string address;
    string contactDetails;
    string email;
    map<string,int>grades;

public:
    Student() = default;
    Student(int rollNumber, const string& name, const string& address, const string& contactDetails, const string& email);

    int getRollNumber() const;
    string getName() const;
    string getAddress() const;
    string getContactDetails() const;
    string getEmail() const;
    map<string, int> getGrades() const;

    void setRollNumber(int rollNumber);
    void setName(const string& name);
    void setAddress(const string& address);
    void setContactDetails(const string& contactDetails);
    void setEmail(const string& email);
    void addGrade(const string& subject, int grade);

    static Student loadFromFile(ifstream& file);
    string toCSV() const;
    static map<int, map<string, int>> loadGradesFromFile(const string& filename);
    void saveGradesToFile(ofstream& file) const;
    string gradesToCSV() const; // Declaration of toCSV method
    void viewProfile() const;
    void viewGrades() const;
};

#endif // STUDENT_H
