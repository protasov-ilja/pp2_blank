#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>

const int DEFAULT_CLIENTS_AMOUNT = 2;
const std::string EXIT_COMMAND_QUIT = "quit";
const std::string EXIT_COMMAND_EXIT = "exit";

bool CheckInputNumber(const std::string& inputString, int& number);
void ShowBankStatistics(CBank* bank);

int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		std::cout << "Invalid arguments count\n"
				  << "Usage: PP2.exe <clients amount>"
				  << "Usage : PP2.exe"
				  << std::endl;

		return 1;
	}

	int clientsAmount = DEFAULT_CLIENTS_AMOUNT;
	if (argc == 2)
	{
		if (!CheckInputNumber(argv[1], clientsAmount))
		{
			return 1;
		}
	}

	CBank* bank = new CBank();

	for (auto i = 0; i < clientsAmount; ++i)
	{
		bank->CreateClient();
	}

	std::string command = "";
	// TODO: WaitForMultipleObjects
	while (EXIT_COMMAND_QUIT != command && EXIT_COMMAND_EXIT != command)
	{
		std::cin >> command;
		std::transform(command.begin(), command.end(), command.begin(), ::tolower);
	}

	ShowBankStatistics(bank);

	return 0;
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
	catch (const std::invalid_argument& ex)
	{
		std::cout << ex.what() << "\n";
		return false;
	}
	catch (const std::out_of_range& ex)
	{
		std::cout << ex.what() << "\n";
		return false;
	}

	return true;
}

void ShowBankStatistics(CBank* bank)
{
	std::cout << "Bank total balance: " << bank->GetTotalBalance() << std::endl;
	std::cout << "Amount of balances of the clients: " << bank->GetClinetsTotalBalance() << std::endl;
	std::cout << "Clients: " << std::endl;
	for each(CBankClient client in bank->GetClients())
	{
		std::cout << "> client " << client.GetId() << ": " << bank->GetClinetBalanceById(client.GetId()) << std::endl;
	}
}
