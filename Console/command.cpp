#include "command.h"
namespace GLBC1
{
	#define HELP "Yor can use the following commands:\n\
	-li\t\t Performs login account.\n\
	-lo\t\t Performs exit from your account.\n\
	-cu\t\t Performs create new account. You must have \nadministrator privileges.\n\
	-gs\t\t Performs request for statistics.\n\
	-cr\t\t Performs change rights on account. You must have \nadministrator privileges.\n\
	\nTo correctly enter login and password they must consist of Latin characters and \
	numbers, and their length does not cause ought exceed 14 characters."
	Command::LogPass::LogPass()
	{
		Clear();
	}

	Command::LogPass::LogPass(const LogPass& lp)
	{
		for (int i = 0; i < 15; i++)
		{
			log[i] = lp.log[i];
			pass[i] = lp.pass[i];
		}
	}

	void Command::LogPass::Clear()
	{
		for (int i = 0; i < 15; i++)
		{
			log[i] = 0;
			pass[i] = 0;
		}
	}

	void Command::ToLower()
	{
		int len;
		len = strlen(com);
		for (int i = 0; i < len; i ++)
		{
			com[i] = tolower(com[i]);
		}
	}

	void Command::IsCommand()
	{
		if ( !strcmp(com,"-li") )
		{
			ncom = CM_LI;
		}
		else if ( !strcmp(com,"-lo") )
		{
			ncom = CM_LO;
		}
		else if ( !strcmp(com,"-cu") )
		{
			ncom = CM_CU;
		}
		else if ( !strcmp(com,"-gs") )
		{
			ncom = CM_GS;
		}
		else if ( !strcmp(com,"-cr") )
		{
			ncom = CM_CR;
		}
		else if ( !strcmp(com,"-help") )
		{
			ncom = CM_HE;
		}
		else if ( !strcmp(com,"-exit") )
		{
			ncom = CM_EXIT;
		}
		else
		{
			ncom = CM_UNKNOWN;
		}
	}

	char Command::GetLP(LogPass& LP)
	{
		char ch;
		int i = 0;
		cout << "Login:";
		while (cin.get(ch) && i != 15)
		{
			if ( !isalnum(ch) )
				break;
			LP.log[i] = ch;
			i++;
		}

		cout << "Password:";
		i = 0;
		while ( ch = getch() )
		{
			if ( !isalnum(ch) || i == 15 )
			{
				cout << '\n';
				break;
			}
			LP.pass[i]=ch;
			i++;
		}

		if ( LP.log[14] !=0 || LP.pass[14] !=0 )
		{
			cout << "Bad login or password. Try Again\n";
			LP.Clear();
			return 0;
		}
		cout << LP.pass << endl;
		return 1;
	}

	char Command::Login()
	{
		cout << "Please enter Login and Password\n";
		if ( !GetLP(user) )
		{
			cout << "No connection with the serwer\n";
			return 0;
		}
		return 1;
	}

	char Command::Logout()
	{
		if (user.log[0] == 0)
		{
			cout << "you are not logged on accunt to get out of it\n";
			return 0;
		}
		else user.Clear();
		cout << "No connection with the serwer\n";
		return 1;
	}

	char Command::CreateUser()
	{
		LogPass LPU, LPA;
		cout << "Please enter Login and Password new user\n";
		if ( !GetLP(LPU) )
		{
			cout << "No connection with the serwer\n";
			return 0;
		}
		cout << "To complete a user, must enter the administrator password\n";
		cout << "Please enter Login and Password admin\n";
		if ( !GetLP(LPA) )
		{
			cout << "No connection with the serwer\n";
			return 0;
		}
		return 1;
	}

	void Command::run()
	{
		switch(ncom)
		{
		case CM_LI: 
			Login();
			break;
		case CM_LO: 
			Logout();
			break;
		case CM_CU:
			CreateUser();
			break;
		case CM_GS:
			cout << "//TODO create user method\n";
			break;
		case CM_CR:
			cout << "//TODO change rights method\n";
			break;
		case CM_HE: 
			cout << HELP << endl;
			break;
		case CM_EXIT:
			cout << "//TODO exit method\n";
			break;
		case CM_UNKNOWN: 
			cout << "Undefined function. To call help, enter -help\n";
			break;
		default:
			cout << "Undefined reference in Command::run switch\n";
			break;
		}
	}

	char Command::GetCommand()
	{
		char ch = 0;
		int i=-1;
		//cout << "COMMAND: "		just as example
		cout << "Please enter the command\n";
		while (cin.get(ch) && ++i<6)
		{
			if (ch == ' ' || ch == '\n')
			{
				com[i] = '\0';
				break;
			}
			com[i]=ch;
		}
		ToLower();
		IsCommand();
		run ();
		cout <<endl;
		return 0;
	}
}