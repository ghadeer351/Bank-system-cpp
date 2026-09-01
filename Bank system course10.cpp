#include<iostream>
#include"clsString.h"
#include"clsDate.h"
#include"clsBankClient.h"
#include"clsValidate.h"
#include"clsUtility.h"
#include"clsMainScreen.h"
#include"clsLogin.h"
using namespace std;

int main()
{
	
	while (true)
	{
		
		if (!clsLogin::ShowLoginScreen())
		{
			
			break;
	    }
	}

	system("pause>0");
}  