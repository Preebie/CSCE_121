#include <iostream>
#include <string>
#include "Student.h"

using std::cout;
using std::endl;

Student::Student(std::string student_id, std::string name):id(student_id), name(name),course_ids({}){
}

std::string Student::get_id() const{
    return id;
}

std::string Student::get_name() const{
    return name;
}

void Student::addCourse(std::string course_id){
    if(course_ids.size() > 0){
        for(size_t n = 0; n < course_ids.size(); n++){
            if(course_id == course_ids.at(n)){
                throw std::invalid_argument("course already exists");
            }
        }
    }
    course_ids.push_back(course_id);
}

void Student::listCourses(std::ostream& os) const{
    if(course_ids.size() == 0){
        os << "Courses for " << id << endl;
        os << "No courses" << endl;
    }
    else{
        os << "Courses for " << id << endl;
        for(size_t i = 0; i < course_ids.size(); i++){
            os << course_ids.at(i) << endl;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Student& s){
    os << s.get_id();
    os << s.get_name();
    return os;
}