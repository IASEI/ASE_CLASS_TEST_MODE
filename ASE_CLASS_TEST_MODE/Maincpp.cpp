#include <iostream>
#include "TraverseDirect.h"
int main()
{
	ASE::TraverseDirect dir(".");
	dir.Traverse();
	getchar();
	return 0;
}