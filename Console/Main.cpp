#include <iostream>
#include "command.h"
using namespace GLBC1;
int main()
{
	Command c;
	while (!c.GetCommand());
	system("pause");
	
	return 0;
}
