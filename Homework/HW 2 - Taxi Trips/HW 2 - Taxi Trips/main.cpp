#include <iostream>
#include <fstream>
#include <string>
#include "taxi_trips.h"
using std::string;
using std::ifstream;
using std::cin;
using std::cout;
using std::endl;

int main() {
    /*string a[] = { "CreditCard", "Check", "Cash", "Bitcoin" };
    cout << is_payment_valid("x", a, 0);*/
    string filename;
    cout << "Enter name of input file: ";
    cin >> filename;
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cout << "Can't open " << filename << endl;

    }
    else {
        double times[10000] = {};
        double distances[10000] = {};
        double costs[10000] = {};
        double tips[10000] = {};
        string types[10000] = {};
        double time = 0;
        double distance = 0;
        double cost = 0;
        double tip = 0;
        string type = "0";
        string worthless = "0";

        int worthlesscounter = 0;
        int timecounter = 0;
        int distancecounter = 0;
        int costcounter = 0;
        int tipcounter = 0;
        int typecounter = 0;
        int highcounter = 0;
        string payment_type[4] = { "CreditCard", "Cash", "Unknown", "NoCharge" };
        while (!ifs.eof()) {
            ifs >> worthless;
            ifs >> time;
            ifs >> distance;
            ifs >> cost;
            ifs >> tip;
            ifs >> type;

            if ((time > 86400) or (distance > 1500) or (cost + tip > 5000) or (!is_payment_valid(type, payment_type, 4)) or ((time == 0) and (distance == 0) and (cost != 0))) {
                worthlesscounter++;
            }
            else {
                times[timecounter] = time;
                distances[distancecounter] = distance;
                costs[costcounter] = cost;
                tips[tipcounter] = tip;
                types[typecounter] = type;
                timecounter++;
                distancecounter++;
                costcounter++;
                tipcounter++;
                typecounter++;
                highcounter++;
            }
        }
        double time_max = max(times, highcounter);
        double time_avg = average(times, highcounter);
        double time_min = min(times, highcounter);
        double time_mode = mode(times, highcounter);

        double distance_max = max(distances, highcounter);
        double distance_avg = average(distances, highcounter);
        double distance_min = min(distances, highcounter);
        double distance_mode = mode(distances, highcounter);

        double cost_max = max(costs, highcounter);
        double cost_avg = average(costs, highcounter);
        double cost_min = min(costs, highcounter);
        double cost_mode = mode(costs, highcounter);

        double tip_max = max(tips, highcounter);
        double tip_avg = average(tips, highcounter);
        double tip_min = min(tips, highcounter);
        double tip_mode = mode(tips, highcounter);
        int tip_zero = length_longest_seq_zeros(tips, highcounter);

        cout << "Number of trips: " << highcounter << endl;
        cout << "Number of trips with invalid data: " << worthlesscounter << endl;
        cout << "Duration: max " << time_max << " min " << time_min << " avg " << time_avg << " mode " << time_mode << endl;
        cout << "Distance: max " << distance_max << " min " << distance_min << " avg " << distance_avg << " mode " << distance_mode << endl;
        cout << "Fare: max " << cost_max << " min " << cost_min << " avg " << cost_avg << " mode " << cost_mode << endl;
        cout << "Tip: max " << tip_max << " min " << tip_min << " avg " << tip_avg << " mode " << tip_mode << endl;
        cout << "Length of longest sequence without tips: " << tip_zero << endl;

        return 0;
    }
}
