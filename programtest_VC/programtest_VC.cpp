#define _CRTDBG_MAP_ALLOC
#include<iostream>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <iostream>
#include "FindDuplicate.h"

int main(int argc, char* argv[])
{
	FindDuplicate finder;
	finder.lookThrough("../../programming_test");
	finder.output();
	getchar();
	finder.~FindDuplicate();
	_CrtDumpMemoryLeaks();
	return 0;
}
