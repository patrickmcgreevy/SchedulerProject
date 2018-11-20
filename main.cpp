#pragma once
#include "Scheduler.h"

int main()
{
	int c = 0;
	string choice = "";

	do {
		cout << "Would you like to (1) Run the program on a test input called \"testinput.txt\", or (2) Run the program with user input: ";

		std::getline(cin, choice);
		std::stringstream(choice) >> c;
		system("cls");
	} while (c != 1 && c != 2);

	if (c == 1)
	{
		Scheduler s1(15);
		s1.runTest();
	}
	else
	{
		cout << "How many processors does the cluster have? " << endl;
		std::getline(cin, choice);
		std::stringstream(choice) >> c;

		Scheduler s2(c);

		s2.run();
	}

}