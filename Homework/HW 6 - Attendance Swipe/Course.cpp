#include <iostream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using std::string;
using std::ostream;
using std::endl;
using std::cout;

Course::Course(std::string id, std::string title, Date startTime, Date endTime):id(id),title(title),startTime(startTime),endTime(endTime){}

std::string Course::getID() const{
    return id;
}
std::string Course::getTitle() const{
    return title;
}
Date Course::getStartTime() const{
    return startTime;
}
Date Course::getEndTime() const{
    return endTime;
}

void Course::addAttendanceRecord(AttendanceRecord ar){
    attendanceRecords.push_back(ar);
}

void Course::outputAttendance(std::ostream& os) const{
    if(attendanceRecords.size() == 0){
        os << "No records" << endl;
    }
    for(size_t n = 0; n < attendanceRecords.size(); n++){
        cout << attendanceRecords[n].getDate().getDateTime() << ",";
        os << attendanceRecords[n].getCourseID() << ",";
        os << attendanceRecords[n].getStudentID() << endl;
    }
}

void Course::outputAttendance(std::ostream& os, std::string student_id) const{
    if(attendanceRecords.size() == 0){
        os << "No records" << endl;
    }
    for(size_t i = 0; i < attendanceRecords.size(); i++){
        if(attendanceRecords[i].getStudentID() == student_id){
            cout << attendanceRecords[i].getDate().getDateTime() << ",";
            os << attendanceRecords[i].getCourseID() << ",";
            os << attendanceRecords[i].getStudentID() << endl;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Course& c){
    os << c.getID();
    os << c.getTitle();
    return os;
}