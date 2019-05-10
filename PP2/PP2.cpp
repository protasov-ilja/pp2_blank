#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include "PrimitiveType.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const int DEFAULT_CLIENTS_AMOUNT = 2;
const std::string EXIT_COMMAND_QUIT = "quit";
const std::string EXIT_COMMAND_EXIT = "exit";
const std::string CRITICAL_SECTION_COMMAND = "critical-section";
const std::string MUTEX_COMMAND = "mutex";
const std::string NONE_PRIMITIVE_COMMAND = "none";
const std::string SHOW_HELP_COMMAND = "/?";


bool CheckInputNumber(const std::string& inputString, int& number);
bool CheckPrimitiveTypeCommand(const std::string& inputString, PrimitiveType& primitiveType);
void ShowBankStatistics(CBank* bank);
void ShowHelpInfo();

int main(int argc, char* argv[])
{
	if ((argc < 2) || (argc > 4))
	{
		std::cout << "Invalid arguments count" << std::endl;
		ShowHelpInfo();

		return 1;
	}

	PrimitiveType primitiveType = PrimitiveType::NONE;
	int clientsAmount = DEFAULT_CLIENTS_AMOUNT;

	if (!CheckPrimitiveTypeCommand(argv[1], primitiveType))
	{
		std::cout << "wrong primitive type "
				  << argv[1] << std::endl;
		ShowHelpInfo();

		return 1;
	}

	if (argc > 2)
	{
		if (argv[2] == SHOW_HELP_COMMAND)
		{
			ShowHelpInfo();
		}
		else if (!CheckInputNumber(argv[2], clientsAmount))
		{
			std::cout << "invalid argument " << argv[2] << std::endl;
			ShowHelpInfo();

			return 1;
		}
	}

	if (argc == 4)
	{
		if (argv[3] == SHOW_HELP_COMMAND)
		{
			ShowHelpInfo();
		}
		else
		{
			std::cout << "invalid argument " << argv[1] << std::endl;
			ShowHelpInfo();

			return 1;
		}
	}

	CBank* bank = new CBank(primitiveType);

	for (auto i = 0; i < clientsAmount; ++i)
	{
		bank->CreateClient();
	}

	std::string command = "";
	// TODO: WaitForMultipleObjects
	while (EXIT_COMMAND_QUIT != command && EXIT_COMMAND_EXIT != command)
	{
		std::getline(std::cin, command);
		std::transform(command.begin(), command.end(), command.begin(), ::tolower);
	}

	ShowBankStatistics(bank);

	return 0;
}

bool CheckPrimitiveTypeCommand(const std::string& inputString, PrimitiveType& primitiveType)
{
	if (inputString == CRITICAL_SECTION_COMMAND)
	{
		primitiveType = PrimitiveType::CRITICAL_SECTION;
		return true;
	}
	else if (inputString == MUTEX_COMMAND)
	{
		primitiveType = PrimitiveType::MUTEX;
		return true;
	}
	else if (inputString == NONE_PRIMITIVE_COMMAND)
	{
		std::cout << inputString << " " << NONE_PRIMITIVE_COMMAND << std::endl;
		primitiveType = PrimitiveType::NONE;
		return true;
	}

	return false;
}

bool CheckInputNumber(const std::string& inputString, int& number)
{
	try
	{
		number = stoi(inputString);
		if (number < 1)
		{
			std::cout << "Argument " << inputString << " is less then 1 or more than max int\n";
			return false;
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		return false;
	}

	return true;
}

void ShowBankStatistics(CBank* bank)
{
	std::cout << "Bank total balance: " << bank->GetTotalBalance() << std::endl;
	std::cout << "Amount of balances of the clients: " << bank->GetClinetsTotalBalance() << std::endl;
	std::cout << "Clients: " << std::endl;
	for (CBankClient client : bank->GetClients())
	{
		std::cout << "> client " << client.GetId() << ": " << bank->GetClinetBalanceById(client.GetId()) << std::endl;
	}
}

void ShowHelpInfo()
{
	std::cout << "Usage: PP2.exe <primitive type> <clients amount> <help>" << std::endl
			  << "Usage: PP2.exe <primitive type> <clients amount>" << std::endl
			  << "Usage: PP2.exe <primitive type> <help>" << std::endl
			  << "Usage : PP2.exe <primitive type>" << std::endl
			  << "<primitive type>: " << std::endl
			  << "> " << CRITICAL_SECTION_COMMAND << " - using critical section as primitive" << std::endl
			  << "> " << MUTEX_COMMAND << " - using mutex as primitive" << std::endl
			  << "> " << NONE_PRIMITIVE_COMMAND << " - do not use any primitives" << std::endl
			  << "<help>: " << std::endl
			  << "> " << SHOW_HELP_COMMAND << " - show help info" << std::endl;
}
