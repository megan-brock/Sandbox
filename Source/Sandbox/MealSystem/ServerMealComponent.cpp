#include "ServerMealComponent.h"

#include "CustomerMealComponent.h"

void UServerMealComponent::SetCurrentCustomer(UCustomerMealComponent* NewCustomer)
{
	if (CurrentCustomer != nullptr)
	{
		CurrentCustomer->SetCurrentServer(nullptr);
	}
	
	CurrentCustomer = NewCustomer;
	OnActiveCustomerChanged.Broadcast(NewCustomer);
}
