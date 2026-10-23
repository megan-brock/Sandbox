#include "FoodItem.h"
#include "MealParticipantComponent.h"

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

void AFoodItem::TakeBite(UMealParticipantComponent* MealParticipant)
{
	if (FoodType == EFoodType::Drink || FoodType == EFoodType::Hand)
	{
		RemovePortion();
	}

	OnBite.Broadcast(MealParticipant);
}

void AFoodItem::PlaceOnTable(FTransform TargetTransform)
{
	OriginalTransform = TargetTransform;
	DetachFromActor( FDetachmentTransformRules::KeepWorldTransform );
	SetActorTransform(TargetTransform, false, nullptr, ETeleportType::TeleportPhysics);
}

void AFoodItem::ResetPosition()
{
	DetachFromActor( FDetachmentTransformRules::KeepWorldTransform );
	SetActorTransform(OriginalTransform, false, nullptr, ETeleportType::TeleportPhysics);
	Interactable = true;
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
