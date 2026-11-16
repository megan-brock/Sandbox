#include "CustomerMealComponent.h"

void UCustomerMealComponent::SetCurrentServer(UServerMealComponent* NewServer)
{
	CurrentServer = NewServer;
	OnActiveServerChanged.Broadcast(CurrentServer);
}
