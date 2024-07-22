#ifndef ADMIN_H
#define ADMIN_H

#include "student.h"
#include <vector>

namespace std {
    class Admin {
    public:
        void addStudent(Student student);
        void updateStudent(Student student);
        void deleteStudent(int rollNumber);
        void viewAllStudents();
    private:
        vector<Student> students;
    };
}

#endif // ADMIN_H
