#pragma once
#include"clsString.h"
#include"clsPerson.h"
#include<fstream>

class clsBankClient :public clsPerson
{
private:

	enum enMode { EmptyMod, UpdateMode, AddNewMode };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkToDelete = false;

	static clsBankClient _ConvertLineToClientObject(string line, string seperator = "#//#")
	{
		vector<string>v = clsString::Split(line, seperator);

		return clsBankClient(enMode::UpdateMode, v[0], v[1], v[2], v[3], v[4], v[5], stod(v[6]));

	}

	static string _ConvertClientObjectToLine(clsBankClient client)
	{
		string line = "";

		line = line + client.FirstName += "#//#";
		line = line + client.LastName += "#//#";
		line = line + client.Email += "#//#";
		line = line + client.Phone += "#//#";
		line = line + client.accountnumber += "#//#";
		line = line + client.pincode += "#//#";
		line = line + to_string(client.accountbalance);

		return line;
	}

	static clsBankClient _GetEmptyClientRecord()
	{
		return clsBankClient(enMode::EmptyMod, "", "", "", "", "", "", 0);
	}

	static void _SaveClientToFail(vector <clsBankClient>& vClient)
	{
		fstream MyFail;
		MyFail.open("ghader", ios::out);

		if (MyFail.is_open())
		{
			for (clsBankClient& c : vClient)
			{
				if (c._MarkToDelete == false)
				{

					MyFail << _ConvertClientObjectToLine(c) << endl;
				}
			}
		}
		MyFail.close();
	}

	struct stTrnsferLogRecord;
	static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTrnsferLogRecord TrnsferLogRecord;
		vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
		TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
		TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
		TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
		TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
		TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];
		return TrnsferLogRecord;
	}

	static vector <clsBankClient>  _LoadDataFromFail()
	{
		vector<clsBankClient> vClient;

		fstream MyFail;
		MyFail.open("ghader", ios::in);

		if (MyFail.is_open())
		{
			string Line;
			while (getline(MyFail, Line))
			{
				vClient.push_back(_ConvertLineToClientObject(Line));
			}
			MyFail.close();
		}
		return vClient;
	}

	void _Update()
	{
		vector < clsBankClient> _vClient;
		_vClient = _LoadDataFromFail();

		for (clsBankClient& c : _vClient)
		{
			if (c.accountnumber == accountnumber)
			{
				c = *this;
				break;
			}
		}
		_SaveClientToFail(_vClient);
	}

	void _AddDataLineToFail(string line)
	{
		fstream MyFail;
		MyFail.open("ghader", ios::app);

		if (MyFail.is_open())
		{
			MyFail << line << endl;
		}
		MyFail.close();
	}

	void _AddNew()
	{
		_AddDataLineToFail(_ConvertClientObjectToLine(*this));
	}

public:

	struct stTrnsferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string UserName;
	};

	clsBankClient(enMode mode, string firstname, string lastname, string email, string phone,
		string accountnumber, string pincode, float accountbalance) :
		clsPerson(firstname, lastname, email, phone)

	{
		_Mode = mode;
		_AccountNumber = accountnumber;
		_PinCode = pincode;
		_AccountBalance = accountbalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMod);
	}

	void setpincode(string pincode)
	{
		_PinCode = pincode;
	}

	string getpincode()
	{
		return _PinCode;
	}
	__declspec(property(get = getpincode, put = setpincode))string pincode;


	void setaccountnumber(string acccountnumber)
	{
		_AccountNumber = acccountnumber;
	}

	string getAccountNumber()
	{
		return _AccountNumber;
	}
	__declspec(property(get = getAccountNumber, put = setaccountnumber))string accountnumber;

	void setAccountBalance(float accountbalance)
	{
		_AccountBalance = accountbalance;
	}

	float getAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = getAccountBalance, put = setAccountBalance))float accountbalance;

	//no UI here
	/*void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";
	}*/

	static clsBankClient Find(string accountnumber)
	{
		vector<clsBankClient>vClientData;

		fstream MyFail;
		MyFail.open("ghader", ios::in );

		if (MyFail.is_open())
		{

			string line;
			while (getline(MyFail, line))
			{
				clsBankClient Client = _ConvertLineToClientObject(line);
				if (Client.getAccountNumber() == accountnumber)
				{
					MyFail.close();
					return Client;
				}
				vClientData.push_back(Client);
			}
			MyFail.close();
		}
		return _GetEmptyClientRecord();
		
	}

	bool Delete()
	{
		vector<clsBankClient>vClient;
		vClient = _LoadDataFromFail();
		for (clsBankClient &c : vClient)
		{
			if (c.accountnumber == _AccountNumber)
			{
				c._MarkToDelete = true;
				break;
			}

		}
		_SaveClientToFail(vClient);
		*this = _GetEmptyClientRecord();

		return true;
	}

	static vector<clsBankClient> GetClientsList() 
	{
		return _LoadDataFromFail();
	}

	static clsBankClient Find(string accountnumber, string pincode)
	{
		vector<clsBankClient>vClientData;

		fstream MyFail;
		MyFail.open("Client.txt", ios::in);

		if (MyFail.is_open())
		{
			cout << "k";
			string line;
			while (getline(MyFail, line))
			{
				clsBankClient Client = _ConvertLineToClientObject(line);
				if (Client.getAccountNumber() == accountnumber && Client.getpincode() == pincode)
				{
					MyFail.close();
					return Client;
				}
				vClientData.push_back(Client);
			}

		}
		return _GetEmptyClientRecord();
	}

	static bool IsClientExiset(string accountnumber)
	{

		clsBankClient Client = Find(accountnumber);

		return(!Client.IsEmpty());
	}

	enum enSaveResult { svFailedEmptyObject, svSuccesed ,svFaildAccountnumberExiset};

 enSaveResult Save()
	{

		switch (_Mode)
		{
		case(enMode::EmptyMod):
		{
			return enSaveResult::svFailedEmptyObject;
			break;
		}

		case(enMode::UpdateMode):
		{
			_Update();
			return enSaveResult::svSuccesed;
			break;
		}

		case(enMode::AddNewMode):
		{
			if (IsClientExiset(_AccountNumber))
			{
				return svFaildAccountnumberExiset;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSuccesed;
			}
		}
		}

	}

 static clsBankClient GetAddNewClientObject(string accountnumber)
 {
	 return clsBankClient(enMode::AddNewMode, "", "", "", "", accountnumber, "", 0);

 }

 void Deposit(double Amount)
 {
	 _AccountBalance += Amount;
	 Save();
 }
 
 bool Withdraw(double Amount)
 {
	 if (Amount > _AccountBalance)
	 {
		 return false;
	 }
	 else
	 {
		 _AccountBalance -= Amount;
		 Save();
		 return true;
	 }
 }

 static double GetTotalBalances() {
	 vector<clsBankClient>vClients = GetClientsList();
	 double TotalBalances = 0;
	 for (clsBankClient& C : vClients) {
		 TotalBalances += C.accountbalance;
	 }
	 return TotalBalances;
 }

 string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient, string UserName, string Seperator = "#//#")
 {
	 string TransferLogRecord = "";
	 TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
	 TransferLogRecord += accountnumber + Seperator;
	 TransferLogRecord += DestinationClient.accountnumber + Seperator;
	 TransferLogRecord += to_string(Amount) + Seperator;
	 TransferLogRecord += to_string(accountbalance) + Seperator;
	 TransferLogRecord += to_string(DestinationClient.accountbalance) + Seperator;
	 TransferLogRecord += UserName;
	 return TransferLogRecord;
 }

 void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
 {
	 string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

	 fstream MyFile;

	 MyFile.open("TransferLog.txt", ios::out | ios::app);

	 if (MyFile.is_open())
	 {
		 MyFile << stDataLine << endl;
		 MyFile.close();
	 }
 }

 bool Transfer(int Ammount, clsBankClient& DestinationClient,string Username)
 {
	 if (Ammount > accountbalance)
	 {
		 return false;
	 }
	 Withdraw(Ammount);
	 DestinationClient.Deposit(Ammount);
	 _RegisterTransferLog(Ammount, DestinationClient, Username);
	 return true;
 }

 static vector <stTrnsferLogRecord> GetTransfersLogList()
 {
	 vector <stTrnsferLogRecord> vTransferLogRecord;
	 fstream MyFile;

	 MyFile.open("TransferLog.txt", ios::in);//read Mode

	 if (MyFile.is_open())
	 {
		 string Line;
		 stTrnsferLogRecord TransferRecord;
		 while (getline(MyFile, Line))
		 {
			 TransferRecord = _ConvertTransferLogLineToRecord(Line);
			 vTransferLogRecord.push_back(TransferRecord);
		 }
		 MyFile.close();
	 }
	 return vTransferLogRecord;
 }

};