#pragma once
#include<iostream>
#include<iomanip>
#include"clsValidate.h"
#include"clsScreen.h"
#include"clsUserDataScreen.h"
#include"clsAddNewUser.h"
#include"clsDeleteUser.h"
#include"clsUpdateUser.h"
#include"clsFindUser.h"

class clsManageUserScreen :protected clsScreen
{
private:
	enum enManageUserMenueOptions{
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eMainMenue =6
	};

	static short ReadManageUsersMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
		return Choice;
	}

	static void _GoBackToManageUsersMenue()
	{
		cout << "\n\nPress any key to go back to Manage Users Menue...";
		system("pause>0");
		ShowManageUsersMenue();
	}

	static void _ShowListUsersScreen()
	{
		//cout << "\nList Users Screen Will Be Here.\n";
		clsListUsersScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		//cout << "\nAdd New User Screen Will Be Here.\n";
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		//cout << "\nDelete User Screen Will Be Here.\n";
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen(){
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUsersMenueOption(enManageUserMenueOptions ManageUsersMenueOption)
	{
		switch (ManageUsersMenueOption)
		{
		case enManageUserMenueOptions::eListUsers:
		{
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case enManageUserMenueOptions::eAddNewUser:
		{
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case enManageUserMenueOptions::eDeleteUser:
		{
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case enManageUserMenueOptions::eUpdateUser:
		{
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case enManageUserMenueOptions::eFindUser:
		{
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case enManageUserMenueOptions::eMainMenue:
		{
			//do nothing here the main screen will handle it :-) ;
		}
		}
	}

public:

	static void ShowManageUsersMenue()
	{


		if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
		{
			return;// this will exit the function and it will not continue
		}

		system("cls");
		_DrawScreenHeader("\t Manage Users Screen", "");
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t Manage Users Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_PerformManageUsersMenueOption((enManageUserMenueOptions)ReadManageUsersMenueOption());
	}

};

