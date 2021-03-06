#include <iostream>
#include <chrono>
#include <ctime>

#include "StringGenerator.h"
#include "Coder.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char ** argv) {
	Coder coder;
	bool cont = true;

	cout << "Commands: " << endl
		<< "quit: quit application" << endl
		<< "encode [string]: encode the given string" << endl
		<< "decode [digest]: decode the given digest (using format generated by this application)" << endl << endl;

	while (cont)
	{
		cout << ">> ";

		string command = "";
		cin >> command;

		if (command == "quit")
		{
			cont = false;
		}
		else if (command == "encode")
		{
			string plain = "";
			cin >> plain;
			cout << coder.Encode(plain) << endl;
		}
		else if (command == "decode")
		{
			string cipher = "";
			cin >> cipher;
			cout << "Running ... ";

			auto start = high_resolution_clock::now();
			string result = coder.Decode(cipher);
			auto end = high_resolution_clock::now();

			cout << "Done in " << (duration_cast<milliseconds>(end.time_since_epoch()) - duration_cast<milliseconds>(start.time_since_epoch())).count() << "ms:" << endl
				 << coder.Decode(cipher) << endl;
		}
		else
		{
			cout << "Error: unknown command" << endl;
		}

		cout << endl;
	}
}
