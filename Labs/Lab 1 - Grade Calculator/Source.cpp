// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
    double hw_average,
    double lw_average,
    double reading,
    double engagement,
    double weighted_total,
    char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
    string* category,
    double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO

    // TODO(student): declare and initialize variables that you want
    double examTotal = 0;
    double examFinal = 0;
    double readingTotal = 0;
    double readingFinal = 0;
    double homeworkTotal = 0;
    double labsTotal = 0;
    double engagementTotal = 0;
    double examGreater;
    int examAmount = 0;
    int readingAmount = 0;
    int homeworkAmount = 0;
    int labAmount = 0;
    int engagementAmount = 0;
    int homeworkPassed = 0;
    int homeworkFailed = 0;
    int labsPassed = 0;
    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            examTotal = examTotal + score;
            examAmount ++;
        }
        else if (category == "final-exam") {
            examFinal = score;
        }
        else if (category == "hw") {
            homeworkTotal = homeworkTotal + score;
            homeworkAmount ++;
        }
        else if (category == "lw") {
            if (score >= 1) {
                labsTotal = labsTotal + 100;
                labAmount ++;
            }
            else {
                labsTotal += 0;
                labAmount ++;
            }
        }
        else if (category == "reading") {
            readingTotal = readingTotal + score;
            readingAmount ++;
        }
        else if (category == "engagement") {
            engagementTotal += score;
            if (engagementTotal > 100) {
                engagementTotal = 100;
            }
            engagementAmount++;
        }
        else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    // TODO(student): compute component averages

    double exam_average = 0;
    double hw_average = 0;
    double lw_average = 0;
    double engagement = 0;
    double reading = 0;

    if (labAmount < 1) {
        labAmount = 1;
    }
    if (homeworkAmount < 1) {
        homeworkAmount = 1;
    }
    if (examAmount < 2) {
        examAmount = 2;
    }
    if (engagementAmount < 1) {
        engagementAmount = 1;
    }
    if (readingAmount < 1) {
        readingAmount = 1;
    }
    hw_average = homeworkTotal / homeworkAmount;
    lw_average = labsTotal / labAmount;
    exam_average = examTotal / examAmount;
    reading = readingTotal / readingAmount + 15;
    engagement = engagementTotal/engagementAmount + 15;
    if (reading > 100) {
        reading = 100;
    }    
    if (engagement > 100) {
        engagement = 100;
    }
    if (exam_average < examFinal) {
        exam_average = examFinal;
    }
    else {
        exam_average = ((exam_average * examAmount) + examFinal) / (examAmount + 1.0);
    }
    // TODO(student): compute weighted total of components
    double weighted_total = (.4 * exam_average) + (.4 * hw_average) + (.1 * lw_average) + (.05 * engagement) + (.05 * reading);

    // TODO(student): compute final letter grade
    char final_letter_grade = 'X';
    if (weighted_total >= 90) {
        final_letter_grade = 'A';
    }
    else if (weighted_total >= 80) {
        final_letter_grade = 'B';
    }
    else if (weighted_total >= 70) {
        final_letter_grade = 'C';
    }
    else if (weighted_total >= 60) {
        final_letter_grade = 'D';
    }
    else {
        final_letter_grade = 'F';
    }
    print_results(
        exam_average, hw_average, lw_average, reading, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | reading | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double reading,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "           reading: " << reading << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}