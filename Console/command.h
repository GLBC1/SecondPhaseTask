#include <iostream>
#include <conio.h>
using namespace std;
namespace GLBC1
{
	class Command
	{
		enum Type 
		{
			CM_LI,
			CM_LO,
			CM_CU,
			CM_GS,
			CM_CR,
			CM_HE,
			CM_EXIT,
			CM_UNKNOWN = 10
		};
		struct LogPass
		{
			char log[15];
			char pass[15];
			LogPass();
			LogPass(const LogPass& lp);
			void Clear();
		};
		char com[6];		// A: command may be more then 6 letters may bee use #define
		char ncom;
		LogPass user;
		//
		void ToLower();
		void IsCommand();
		char GetLP(LogPass& LP);
		char Login();
		char Logout();
		char CreateUser();
		void run();
	public:
		char GetCommand();
	};
}