#pragma once
#include<iostream>
#include"clsUser.h"
#include"Global.h"
#include"clsDate.h"
using namespace std;

class clsScreen
{
protected:

	static void _DrawScreenHeader(string title,string SubTitle="")
	{
		cout << "\n\n\t\t\t\t\t----------------------------------------\n";
			cout << "\n\t\t\t\t\t" << title << endl;
			if (SubTitle != "")
			{
				cout << "\t\t\t\t\t" << SubTitle << endl;
			}
			cout << "\n\t\t\t\t\t----------------------------------------\n\n";
			cout <<"\t\t\t\t\t\tUser Name: " << CurrentUser.UserName;
			cout << "\n\t\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << endl << endl;
	}


	static bool CheckAccessRights(clsUser::enPermissions Permissions)
	{
		if (!CurrentUser.CheckAccessPermissions(Permissions))
		{
			cout << "\t\t\t\t\t______________________________________";
			cout << "\n\n\t\t\t\t\t Access Denied! Contact your Admin.";
			cout << "\n\t\t\t\t\t______________________________________\n\n";
			return false;
		}
		else
		{
			return true;
		}

	}

};

