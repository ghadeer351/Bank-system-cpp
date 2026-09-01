#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsValidate.h"
#include <iomanip>
class clsAddNewClientScreen : protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();
		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();
		cout << "\nEnter PinCode: ";
		Client.pincode = clsInputValidate::ReadString();
		cout << "\nEnter Account Balance: ";
		Client.accountbalance = clsInputValidate::ReadDblNumber();
	}

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName : " << Client.FirstName;
		cout << "\nLastName : " << Client.LastName;
		cout << "\nFull Name : " << Client.FullName();
		cout << "\nEmail : " << Client.Email;
		cout << "\nPhone : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.accountnumber;
		cout << "\nPassword : " << Client.pincode;
		cout << "\nBalance : " << Client.accountbalance;
		cout << "\n___________________\n";
	}

public:

	static void ShowAddNewClientScreen()
	{


		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;// this will exit the function and it will not continue
		}

		_DrawScreenHeader("\t Add New Client Screen", "");

		string AccountNumber = "";

		cout << "\nPlease Enter Account Number: ";

		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExiset(AccountNumber))
		{
			cout << "\nAccount Number Is Already Used, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResult SaveResult;

		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResult::svSuccesed:
		{
			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintClient(NewClient);
			break;
		}
		case clsBankClient::enSaveResult::svFailedEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;
		}
		case clsBankClient::enSaveResult::svFaildAccountnumberExiset:
		{
			cout << "\nError account was not saved because account number is used!\n";
			break;
		}
		}
	}
};