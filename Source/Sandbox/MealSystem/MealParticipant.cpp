#include "MealParticipant.h"

#include "MealAreaManager.h"

void UMealParticipant::EnterMealArea(AMealAreaManager* AreaManager)
{
	MealAreaManager = AreaManager;
	
	if (AutoRegister)
	{
		MealAreaManager->Register(this);
	}
	
	OnFoodAreaChanged.Broadcast(MealAreaManager);
}

void UMealParticipant::LeaveMealArea()
{
	if (MealAreaManager)
	{
		MealAreaManager->Unregister(this);
	}
	
	MealAreaManager = nullptr;
	
	OnFoodAreaChanged.Broadcast(nullptr);
}
