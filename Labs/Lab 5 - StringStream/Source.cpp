#include <iostream>
#include <sstream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::ifstream;

using std::istringstream;
using namespace std;

int main() {
    string filename;
    cout << "Enter donation filename: ";
    cin >> filename;
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cout << "Failed to open file " << filename << "." << endl;
        return 1;
    }
    double currentTotal = 0;
    int currentCollector = 0;
    int numDon = 0;
    double maxTotalDonation = 0;
    int maxTotalCollector = 0;
    string number1;
    while (!ifs.eof()) {
        ifs >> number1;

        if (number1.size() == 9) {
            currentCollector = stoi(number1, nullptr, 10);
            currentTotal = 0;
            numDon = 0;
        }
        else {
            double number = stod(number1, nullptr);
            currentTotal += number;
            numDon++;
        }
       /* double number = stod(number1, nullptr);
        if (number < 100000000) {            
            currentTotal += number;
            numDon++;
        }*/
        /*else if ((number.length() < 9)) {
            double x = stoi(number, nullptr, 10);
            cout << number << endl;
            currentTotal += x;
            numDon++;
        }*/
        if ((currentTotal > maxTotalDonation) && (numDon != 1)) {
            maxTotalDonation = currentTotal;
            maxTotalCollector = currentCollector;
        }
        
    }

    // read data
    if (maxTotalDonation == 0) {
        cout << "No donations." << endl;
    }
    else {
        cout << "Highest donation total: " << maxTotalDonation << endl;
        cout << "-- collected by id: " << maxTotalCollector << endl;
    }
}