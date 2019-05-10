#pragma once
#include <iostream>
#include <vector>
#include <map>

#include <windows.h>
#include "BankClient.h"

class CBank
{
public:
	CBank();
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	int GetTotalBalance() const;
	int GetClinetsTotalBalance() const;
	std::vector<CBankClient> GetClients() const;
	int GetClinetBalanceById(unsigned clientId);

private:
	void SetTotalBalance(int value);
	void SomeLongOperations();

	std::vector<CBankClient> m_clients;
	std::map<unsigned, int> m_clientsBalance;
	int m_totalBalance;
};