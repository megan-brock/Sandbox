#include "CombatWorldSubsystem.h"

void UCombatWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

void UCombatWorldSubsystem::QueueAction(AActor* ActingCombatant, FQueuedAction Action)
{
}

void UCombatWorldSubsystem::CommitTurnActions()
{
}
