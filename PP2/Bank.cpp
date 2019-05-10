#include "Bank.h"

CBank::CBank()
{
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
}

CBankClient* CBank::CreateClient()
{
	unsigned clientId = unsigned(m_clients.size());

	CBankClient* client = new CBankClient(this, clientId);
	std::cout << "Client " << (*client).GetId() << std::endl;
	m_clients.push_back(*client);
	m_clientsBalance.insert(std::pair<char, int>((*client).GetId(), 0));

	return client;
}

void CBank::UpdateClientBalance(CBankClient& client, int value)
{
	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId()
			  << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;

	SomeLongOperations();
	totalBalance += value;
	m_clientsBalance[client.GetId()] += value;

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance != GetTotalBalance() + value)
	{
		std::cout << "! ERROR !" << std::endl;
	}

	SetTotalBalance(totalBalance);
}

void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}

void CBank::SomeLongOperations()
{
	Sleep(1000);
}

int CBank::GetTotalBalance() const
{
	return m_totalBalance;
}

int CBank::GetClinetsTotalBalance() const
{
	int totalBalance = 0;
	for (auto it = m_clientsBalance.begin(); it != m_clientsBalance.end(); ++it)
	{
		totalBalance += it->second;
	}

	return totalBalance;
}

std::vector<CBankClient> CBank::GetClients() const
{
	return m_clients;
}

int CBank::GetClinetBalanceById(unsigned clientId)
{
	return m_clientsBalance[clientId];
}
