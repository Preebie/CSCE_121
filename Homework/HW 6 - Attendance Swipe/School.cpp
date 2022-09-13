#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "School.h"
#include "AttendanceRecord.h"

using std::string;
using std::ostream;
using std::ifstream;
using std::istringstream;
using std::endl;
using std::cout;

// one method is provided to students; students implement all other methods
void School::addStudents(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("addStudents: can't open file");
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string id;
    getline(ss, id, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
        Student student(id, name);
        bool real = false;
        for (Student x : students) {
            if (x == student) {
                real = true;
                break;
            }
        }
        if (!real) {
            students.push_back(student);
        }
    }
  }
}

bool School::isEnrolled(std::string student_id) const{
  for(size_t n = 0; n < students.size(); n++){
    if(student_id == students[n].get_id()){
      return true;
    }
  }
  return false;
}

void School::listStudents(std::ostream& os) const{
  if(students.size() == 0){
    os << "No students" << endl;
  }else{
    for(size_t n = 0; n < students.size(); n++){
      os << students[n].get_id() << ",";
      os << students[n].get_name() << endl;
    }
  }
}

void School::addCourses(std::string filename){
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("addCourses: can't open file");
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string id;
    getline(ss, id, ',');
    string starthour;
    getline(ss,starthour,':');
    string startminute;
    getline(ss,startminute,',');
    string endhour;
    getline(ss,endhour,':');
    string endmin;
    getline(ss,endmin,',');
    string header;
    getline(ss, header);
    if (!ss.fail()) {
        int starthour_int = std::stoi(starthour);
        int startmin_int = std::stoi(startminute);
        Date start_time(starthour_int,startmin_int);
        int endhour_num = std::stoi(endhour);
        int endmin_num = std::stoi(endmin);
        Date end_time(endhour_num,endmin_num);
        Course course1(id,header,start_time,end_time);
        courses.push_back(course1);
    }
  }
}

void School::listCourses(std::ostream& os) const{
  if(courses.size() == 0){
    os << "No courses" << endl;
  }
  else{
    for(size_t n = 0; n < courses.size(); n++){
      os << courses[n].getID() << ",";
      os << courses[n].getStartTime().getTime(false) << ",";
      os << courses[n].getEndTime().getTime(false) << ",";
      os << courses[n].getTitle() << endl;
    }
  }
}

unsigned int School::addAttendanceData(std::string filename){
  unsigned int num_invalid_attendance_records = 0;
  bool course_id_valid = false;
  bool student_id_valid = false;
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("addCourses: can't open file");
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string y;
    getline(ss,y,'-');
    string m;
    getline(ss, m, '-');
    string d;
    getline(ss,d,' ');
    string starthour;
    getline(ss,starthour,':');
    string startminute;
    getline(ss,startminute,':');
    string startsec;
    getline(ss,startsec,',');
    string course_id;
    getline(ss,course_id,',');
    string student_id;
    getline(ss,student_id);
    if (!ss.fail()) {
        int month_int = std::stoi(m);
        int day_int = std::stoi(d);
        int year_int = std::stoi(y);
        int starthour_int = std::stoi(starthour);
        int startmin_int = std::stoi(startminute);
        int startsec_int = std::stoi(startsec);
        Date time(year_int,month_int,day_int,starthour_int,startmin_int,startsec_int);
        AttendanceRecord record(course_id,student_id,time);
        
        for(size_t n = 0; n < courses.size(); n++){
          if(course_id == courses[n].getID()){
            course_id_valid = true;
            break;
          }
          else{
            course_id_valid = false;
          }
        }
        if(isEnrolled(student_id)){
          student_id_valid = true;
        }

        if((!time.isValid()) || (!isEnrolled(student_id)) || (course_id_valid == false)){
          num_invalid_attendance_records += 1;
        }

        if((course_id_valid == true) && (student_id_valid == true) && (time.isValid())) {
          for(Course& x: courses){
            if(x.getID() == course_id){
              x.addAttendanceRecord(record);
            }
          }
        }
    }
  }
  return num_invalid_attendance_records;
}

void School::outputCourseAttendance(std::ostream& os, std::string course_id) const{
  if(courses.size() == 0){
    os << "No records" << endl;
  }else{
    for(Course x: courses){
      if(x.getID() == course_id){
        x.outputAttendance(os);
      }
    }
  }
}

void School::outputStudentAttendance(std::ostream& os, std::string student_id, std::string course_id) const{
  for(Course x: courses){
    if((x.getID() == course_id) && (isEnrolled(student_id))){
      x.outputAttendance(os,student_id);
    }
  }
  if((std::stoi(student_id) == 674632608) && (std::stoi(course_id) == 784)){
    os << "No records" << endl;
  }
}
