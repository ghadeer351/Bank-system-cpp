#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsValidate.h"
class clsUpdateClientScreen :protected clsScreen
{
private:
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

	static void ReadClientInfo(clsBankClient& Client)
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

public:

	static void ShowUpdateClientScreen()
	{

		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;// this will exit the function and it will not continue
		}

		_DrawScreenHeader("\tUpdate Client Screen", "");
		string AccountNumber = "";
		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExiset(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);
		cout << "\nAre you sure you want to update this client y/n? ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "\n\nUpdate Client Info:";
			cout << "\n____________________\n";
			ReadClientInfo(Client1);
			clsBankClient::enSaveResult SaveResult;
			SaveResult = Client1.Save();
			switch (SaveResult)
			{
			case clsBankClient::enSaveResult::svSuccesed:
			{
				cout << "\nAccount Updated Successfully :-)\n";
				_PrintClient(Client1);
				break;
			}
			case clsBankClient::enSaveResult::svFailedEmptyObject:
			{
				cout << "\nError account was not saved because it's Empty";
				break;
			}
			}
		}
	}
};