#include "MealAreaManager.h"

#include "CustomerMealComponent.h"
#include "ServerMealComponent.h"

void AMealAreaManager::Register(UMealParticipant* MealParticipant)
{
	if (UServerMealComponent* Server = Cast<UServerMealComponent>(MealParticipant))
	{
		if (AvailableFoodServers.Contains(Server))
		{
			return;
		}
	
		AvailableFoodServers.Add(Server);
	}

	if (UCustomerMealComponent* Customer = Cast<UCustomerMealComponent>(MealParticipant))
	{
		if (WaitingCustomers.Contains(Customer))
		{
			return;
		}
	
		WaitingCustomers.Add(Customer);
	}
	
	MatchServersToCustomers();
}

void AMealAreaManager::Unregister(UMealParticipant* MealParticipant)
{
	if (UServerMealComponent* Server = Cast<UServerMealComponent>(MealParticipant))
	{
		AvailableFoodServers.Remove(Server);
	}
	
	if (UCustomerMealComponent* Customer = Cast<UCustomerMealComponent>(MealParticipant))
	{
		WaitingCustomers.Remove(Customer);
	}
}

bool AMealAreaManager::IsRegistered(UMealParticipant* MealParticipant)
{
	if (UServerMealComponent* Server = Cast<UServerMealComponent>(MealParticipant))
	{
		return AvailableFoodServers.Contains(Server);
	}
	
	if (UCustomerMealComponent* Customer = Cast<UCustomerMealComponent>(MealParticipant))
	{
		return WaitingCustomers.Contains(Customer);
	}
	
	return false;
}

void AMealAreaManager::MatchServersToCustomers()
{
	if (WaitingCustomers.IsEmpty() || AvailableFoodServers.IsEmpty())
	{
		return;
	}
	
	UCustomerMealComponent* Customer = WaitingCustomers[0];
	UServerMealComponent* FoodServer = AvailableFoodServers[0];
	
	FoodServer->SetCurrentCustomer(Customer);
	Customer->SetCurrentServer(FoodServer);
	
	WaitingCustomers.RemoveAt(0);
	AvailableFoodServers.RemoveAt(0);
}
