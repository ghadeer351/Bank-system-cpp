#pragma once
#include<iostream>
#include"clsUser.h"
#include"Global.h"
#include"clsMainScreen.h"
#include<cstdlib>
using namespace std;

class clsLogin :public clsScreen
{

	static bool _Login()
	{
		//clsUser CurrentUser = clsUser::Find("", "");
		bool LoginFaild = false;
		int tr = 0;
		string username, password;
		
		do
		{
			if (LoginFaild)
			{
				tr++;
			
				cout << "\n\033[1;31m Invalid use name or password,try again: \n\033[0m";
				cout << "\033[1;31m you have [" << 3-tr << "] trails to login\n\033[0m";
			}

			if (tr == 3)
			{
			
				
				system("cls");
				system("color 4");
				cout << "\n\n\n\n\n\n\n\n\a\t\t\t\t\t\tsystem is locked\n\n";
				system("pause>0");
				return false;
			}

			
			cout << "\n Enter user name: ";
			cin >> username;

			cout << "\n Enter password: ";
			cin >> password;
			
			CurrentUser = clsUser::Find(username, password);

			

			LoginFaild = CurrentUser.IsEmpty();
		} while (LoginFaild);
	
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t   Login Screen");
		return _Login();
	}
};