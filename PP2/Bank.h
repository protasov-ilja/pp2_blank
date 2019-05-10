#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <mutex>

#include <windows.h>
#include "BankClient.h"
#include "PrimitiveType.h"

class CBank
{
public:
	CBank(PrimitiveType primitiveType);
	~CBank();
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	int GetTotalBalance() const;
	int GetClinetsTotalBalance() const;
	std::vector<CBankClient> GetClients() const;
	int GetClinetBalanceById(unsigned clientId);

private:
	void SetTotalBalance(int value);
	void SomeLongOperations();
	void LockProcess();
	void UnlockProcess();

	std::vector<CBankClient> m_clients;
	std::map<unsigned, int> m_clientsBalance;
	int m_totalBalance;
	CRITICAL_SECTION m_criticalSection;
	std::mutex m_mutex;
	PrimitiveType m_primitiveType;
};