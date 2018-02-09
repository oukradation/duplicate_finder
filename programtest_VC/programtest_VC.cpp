#include <iostream>
#include "FindDuplicate.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Usage : excutable.exe <path>" << endl;
		return 1;
	}

	FindDuplicate finder;

	finder.lookThrough(argv[1]);
	
	cout << "Level 1 output : " << endl;
	finder.output();

	cout << "\n\nLevel 3 output : " << endl;
	finder.groupoutput();

	finder.~FindDuplicate();
	return 0;
}
