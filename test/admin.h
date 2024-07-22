#ifndef ADMIN_H
#define ADMIN_H
#include <vector>
#include "student.h"

using namespace std;
class Admin {
private:
    vector<Student> students;

public:
    void addStudent(const Student& student);
    void viewStudents();
    void updateStudent(int rollNumber);
    void deleteStudent(int rollNumber);
    void addGrades(int rollNumber);
    void saveStudentsToFile();
    Student* findStudentByRollNumber(int rollNumber);
    void saveGradesToFile() const;
};

#endif
