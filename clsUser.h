#pragma once
#include<iostream>
#include<fstream>
#include"clsPerson.h"
#include"clsString.h"
#include <string>
#include"clsUtility.h"
using namespace std;

class clsUser :public clsPerson
{
private:

	enum enMode { EmptyMode, AddMode, UpdateMode };
	enMode _Mode;
	string _UserName;
	string _PassWord;
	int _Permissions;
	bool _MarkedForDelete=false;

	struct stLoginRegisterRecord;
	
	string _PrepareLogInRecord(string Seperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += to_string(Permissions);
		return LoginRecord;
	}

	static clsUser _ConvertLineToUserObject(string line, string Seperator = "#//#")
	{
		vector<string>vUserData = clsString::Split(line, Seperator);
		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3],
			vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
	};

	static string _ConvertFromUserObjectToLine(clsUser User, string Seperator = "#//#")
	{
		return  User.FirstName + Seperator
			+ User.LastName + Seperator
			+ User.Email + Seperator
			+ User.Phone + Seperator
			+ User.UserName + Seperator
			+clsUtil::EncryptText(User.PassWord) + Seperator
			+ to_string(User.Permissions);
	};

	static vector<clsUser> _LoadUserDataFromFile()
	{
		vector<clsUser>vUsers;
		fstream MyFile;
		MyFile.open("Users.txt", ios::in );

		if (MyFile.is_open())
		{
			string line = "";
			while (getline(MyFile, line))
			{
				vUsers.push_back(_ConvertLineToUserObject(line));
			}
			MyFile.close();
		}
		return vUsers;
	}

	static void _SaveUserDataToFail(vector<clsUser>vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsUser& User : vUsers) {
				if (User._MarkedForDelete == false) {
					MyFile << _ConvertFromUserObjectToLine(User) << endl;
				}
			}
			MyFile.close();
		}
	}

	static void _AddDataLineToFile(string stDataLine) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsUser>vUsers = _LoadUserDataFromFile();
		for (clsUser& c : vUsers)
		{
			if (c.UserName == _UserName)
			{
				c = *this;
				break;
			}
		}
		_SaveUserDataToFail(vUsers);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertFromUserObjectToLine(*this));
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;
		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[2]);
		return LoginRegisterRecord;
	}

public:
	
	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		int Permissions;
	};

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64
		,pLoginRegister = 128
	};


	clsUser(enMode Mode, string firstname, string lastname, string email, string phone,
		string username, string password, int permissions) :clsPerson(firstname,
			lastname, email, phone)
	{
		_Mode = Mode,
			_PassWord = password;
		_UserName = username;
		_Permissions = permissions;
	}


	void set_UserName(string UserName) {
		_UserName = UserName;
	}

	void set_PassWord(string PassWord) {
		_PassWord = PassWord;
	}

	void set_Permissions(int Permissions) {
		_Permissions = Permissions;
	}

	string get_UserName() { return _UserName; }

	string get_PassWord() { return _PassWord; }

	int get_Permissions() { return _Permissions; }

	_declspec(property(get = get_UserName, put = set_UserName))string UserName;
	_declspec(property(get = get_PassWord, put = set_PassWord))string PassWord;
	_declspec(property(get = get_Permissions, put = set_Permissions))int Permissions;


	static clsUser Find(string UserName) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			string Line = "";
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName) {
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string PassWord)
	{
		fstream MyFile;
	
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			string Line = "";
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.PassWord == PassWord) 
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
	
		return _GetEmptyUserObject();
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete() {
		return _MarkedForDelete;
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsUser::EmptyMode:
		{
			if (IsEmpty())
			{
				return svFaildEmptyObject;
			}
			break;
		}
		case clsUser::UpdateMode:
		{
			_Update();
			return svSucceeded;
			break;
		}
		case clsUser::AddMode:
		{
			if (clsUser::IsUserExist(this->UserName)) {
				return enSaveResults::svFaildUserExists;
			}
			else {
				_AddNew();
				this->_Mode = UpdateMode;
				return svSucceeded;
			}
			break;
		}
		default:
			break;
		}
	}

	bool Delete() {
		vector<clsUser>vUsers = _LoadUserDataFromFile();
		for (clsUser& U : vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._MarkedForDelete = true;
				break;
			}
		}
		_SaveUserDataToFail(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUserDataFromFile();
	}

	 bool CheckAccessPermissions(enPermissions Permissions)
	{
		 if (this->Permissions==enPermissions::eAll)
		 {
			 return true;
		}
		 else if ((this->Permissions & Permissions))
		 {
			 return true;
		 }
		 return false;
	}

	 void RegisterLogIn()
	 {
		 string stDataLine = _PrepareLogInRecord();
		 fstream MyFile;
		 MyFile.open("LoginRegister.txt", ios::out | ios::app);
		 if (MyFile.is_open())
		 {
			 MyFile << stDataLine << endl;
			 MyFile.close();
		 }
	 }

	 static vector <stLoginRegisterRecord> GetLoginRegisterList()
	 {
		 vector <stLoginRegisterRecord> vLoginRegisterRecord;
		 fstream MyFile;
		 MyFile.open("LoginRegister.txt", ios::in);//read Mode
		 if (MyFile.is_open())
		 {
			 string Line;
			 stLoginRegisterRecord LoginRegisterRecord;
			 while (getline(MyFile, Line))
			 {
				 LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
				 vLoginRegisterRecord.push_back(LoginRegisterRecord);
			 }
			 MyFile.close();
		 }
		 return vLoginRegisterRecord;
	 }

};



    
