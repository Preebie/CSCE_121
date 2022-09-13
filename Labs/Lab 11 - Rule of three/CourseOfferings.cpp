#include <iostream>
#include <string>
#include "Course.h"
#include "Section.h"
#include "CourseOfferings.h"

using std::string;
using std::endl;

/* TODO-STUDENT: implement the Rule of Three member functions:
** copy constructor, copy assignment operator, destructor
*/

CourseOfferings::~CourseOfferings() {
	//std::cout << "destroy" << std::endl;
	delete[] sectionList;
	sectionList = nullptr;
	capacity = 0;
}

CourseOfferings::CourseOfferings(const CourseOfferings & course) :course(course.course), year(course.year), semester(course.semester), nbSections(course.nbSections), capacity(course.capacity), sectionList(nullptr) {
	//std::cout << "test copy" << std::endl;
	sectionList = new Section[capacity];
	for (size_t i = 0; i < nbSections; i++) {
		sectionList[i] = course.sectionList[i];
	}
}

CourseOfferings& CourseOfferings::operator =(const CourseOfferings & right) {
	//std::cout << "test copy" << std::endl;
	if (this != &right) {
		delete[] sectionList;
		course = right.course;
		capacity = right.capacity;
		year = right.year;
		nbSections = right.nbSections;
		semester = right.semester;
		sectionList = new Section[capacity];
		for (size_t i = 0; i < nbSections; i++) {
			sectionList[i] = right.sectionList[i];
		}
	}
	return *this;
}


/* TODO-STUDENT: implement this function
** Parameters: none
** Return value: none
** Functionality: It updates the object to increase the capacity
**                of the atribute member sessionList.
**                If capacity is zero, it becomes one.
**                If capacity is greater than zero, it is doubled.
*/
void CourseOfferings::increaseSectionListCapacity() {
	// student will implement this one
	if (capacity == 0) {
		capacity = 1;
		sectionList = new Section[capacity];
	}
	else {
		Section* temp = new Section[capacity * 2];
		for (int i = 0; i < capacity; i++) {
			temp[i] = sectionList[i];
		}
		delete[] sectionList;
		sectionList = temp;
		capacity *= 2;
	}
}

/* TODO-STUDENT: implement this function
** Parameters: none
** Return value: none
** Functionality: it updates the object so that nbSessions becomes zero.
*/
void CourseOfferings::clearSections() {
	// student will implement this one
	nbSections = 0;
}

/* TODO-STUDENT: implement this function
** Parameters: none
** Return value: none
** Functionality: it updates the object so that nbSessions and capacity become zero,
**                updating sessionList accordingly.
*/
void CourseOfferings::fullClearSections() {
	// student will implement this one
	nbSections = 0;
	capacity = 0;
	delete[] sectionList;
}

/* TODO-STUDENT: implement this function
*/
//std::ostream& operator<<(std::ostream & os, const CourseOfferings & course) {
//	// student will implement this one
//	os << course.getYear();
//	os << course.getSemester();
//	for (int i = 0; i < course.getNumberSections(); i++) {
//	}
//	return os;
//}

CourseOfferings::CourseOfferings(Course c, unsigned int year, char semester)
	: course(c), year(year), semester(semester) {
	capacity = 0;
	nbSections = 0;
	sectionList = nullptr;
}


CourseOfferings::CourseOfferings(unsigned int year, char semester,
	const CourseOfferings & co)
	: CourseOfferings(co) {
	this->year = year;
	this->semester = semester;
}

void CourseOfferings::addSection(const Section & s) {
	if (nbSections == capacity) {
		increaseSectionListCapacity();
	}
	sectionList[nbSections++] = s;
}

size_t CourseOfferings::findSection(string section) {
	for (size_t i = 0; i < nbSections; i++) {
		if (sectionList[i].getId() == section) {
			return i;
		}
	}
	return npos;
}

void CourseOfferings::replaceInstructor(string section, string instructor) {
	size_t idx = findSection(section);
	if (idx == npos) {
		throw std::invalid_argument("section not found");
	}
	else {
		sectionList[idx].setInstructor(instructor);
	}
}

string CourseOfferings::getInstructor(string section) {
	size_t idx = findSection(section);
	if (idx == npos) {
		throw std::invalid_argument("section not found");
	}
	else {
		return sectionList[idx].getInstructor();
	}
}

bool operator==(const CourseOfferings & left, const CourseOfferings & right) {
	if (!(left.getYear() == right.getYear()
		&& left.getSemester() == right.getSemester()
		&& left.getCourse().getId() == right.getCourse().getId()
		&& left.getCourse().getTitle() == right.getCourse().getTitle()
		&& left.getNumberSections() == right.getNumberSections()
		&& left.getSectionListCapacity() == right.getSectionListCapacity())) {
		return false;
	}

	// checking sections
	for (size_t i = 0; i < left.getNumberSections(); i++) {
		Section left_new = left.getSectionList()[i];
		Section right_new = right.getSectionList()[i];
		if (!(left_new.getId() == right_new.getId()
			&& left_new.getTime() == right_new.getTime()
			&& left_new.getLocation() == right_new.getLocation()
			&& left_new.getInstructor() == right_new.getInstructor())) {
			return false;
		}
	}
	return true;
}
