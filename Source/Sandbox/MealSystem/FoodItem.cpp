#include "FoodItem.h"
#include "CustomerMealComponent.h"
#include "MealParticipant.h"

AFoodItem::AFoodItem()
{
	InteractableItemComponent = CreateDefaultSubobject<UInteractableItemComponent>(TEXT("InteractableItemComponent"));
}

void AFoodItem::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalTransform = GetActorTransform();
}

bool AFoodItem::HasRemaining()
{
	return BitesRemaining > 0;
}

bool AFoodItem::RemovePortion()
{
	if (BitesRemaining <= 0)
	{
		return false;
	}
	
	BitesRemaining--;
	
	if (BitesRemaining <= 0)
	{
		if (NeedsCollectionAfterFinishing)
		{
			ReadyForCollection = true;
			Interactable = false;
		}
		else
		{
			Destroy();
			OnFinished.Broadcast();
		}
	}
	
	return true;
}

void AFoodItem::TakeBite(UCustomerMealComponent* Customer)
{
	RemovePortion();
	OnBite.Broadcast(Customer);
}


void AFoodItem::PlaceOnTable(FTransform TargetTransform)
{
	InteractableItemComponent->OriginalTransform = TargetTransform;
	InteractableItemComponent->Drop();
}

bool AFoodItem::TryCollect()
{
	if (!NeedsCollectionAfterFinishing || !ReadyForCollection)
	{
		return false;
	}
	
	ReadyForCollection = false;
	
	OnFinished.Broadcast();
	
	return true;
}
