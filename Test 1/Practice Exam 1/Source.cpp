#include <iostream>;
#include <string>;
#include <fstream>;
#include <sstream>;

using namespace std;
using std::string;

int none() {
	ifstream fin("prohibited.txt");

	if (!fin.is_open()) {

		cout << "ERROR: can't read file" << endl;
		return 1;

	}

	string prohibited[INT8_MAX] = {};
	string word;
	int counter = 0;

	while (!fin.eof()) {

		fin >> word;
		prohibited[counter] = word;
		counter++;

	}
	ifstream fins("tenants.txt");
	int itemscount;
	string line = " ";
	int counter2 = 0;
	string items[INT8_MAX] = {};
	string names[INT8_MAX] = {};
	int namecount = 0;
	string illegals[INT8_MAX] = {};
	int illegal = 0;
	while (getline(fins, line))	{
		size_t x = line.find_first_of(' ');
		string name = line.substr(0, x);
		names[namecount] = name;
		namecount++;
		line = line.substr(x);
		itemscount = 0;
		stringstream iss(line);
		
		while (iss >> word) {
			items[counter2] = word;
			counter2++;
			itemscount++;
		}
		bool isProhibited = false;
		for (int n = 0; n < counter2;n++) {
			for (int y = 0; y < counter;y++) {
				if (items[n] == prohibited[y]) {
					isProhibited = true;
					
				}
			}
		}
		if (isProhibited) {
			
			illegals[illegal] = names[namecount - 1];
			illegal++;
			illegals[illegal] = " not safe\n";
			illegal++;
		}
		else {
			illegals[illegal] = names[namecount - 1];
			illegal++;
			illegals[illegal] = " safe\n";
			illegal++;
		}
		
	}
	int evens = 0;
	for (int n = 0; n < illegal;n++) {
		cout << illegals[n];
		evens++;
		if (evens % 2 == 1) {
			cout << ":";
		}
	}
	
	fin.close();
}