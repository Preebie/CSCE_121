#include <iostream>
#include <string>

using namespace std;

int main() {
	string x = "null";
	while (x != "quit") {
		int n = 0;
		cout << "Please Enter A Number: ";
		cin >> n;
		cout << endl;


		for (int x = 0; x < n; x++) {
			if ((x * (x - 1) * (x - 2)) == n) {
				cout << n << " is triangular!" << endl;
				cout << "It is triangular when " << x - 2 << " and " << x - 1 << " and " << x << " are multiplied together!";
			}
		}
		cout << "\nAgain?";
		cin >> x;
	}
	

	
}