#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "CombatWorldSubsystem.generated.h"

class UGameplayAbility;

UENUM(BlueprintType)
enum class ETurnPhase : uint8
{
	EnemyExecuting,
	PlayerSelecting,
	PlayerExecuting
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseChanged, ETurnPhase, NewPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTimerUpdated, float, RemainingTime, float, NormalizedProgress);

USTRUCT(BlueprintType)
struct FQueuedAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag AbilityTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TargetCombatant = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StaminaCost = 50;
};

UCLASS(Blueprintable)
class UCombatWorldSubsystem : public UTickableWorldSubsystem
{
public:
	GENERATED_BODY()
	
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UTurnManagerSubsystem, STATGROUP_Tickables); }
	
public:
	UFUNCTION(BlueprintCallable, Category="Combat")
	void QueueAction(AActor* ActingCombatant, FQueuedAction Action);

	UFUNCTION(BlueprintCallable, Category="Combat")
	void CommitTurnActions();
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Turn System|Events")
	FOnPhaseChanged OnPhaseChanged;

	UPROPERTY(BlueprintAssignable, Category = "Turn System|Events")
	FOnTimerUpdated OnTimerUpdated;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	ETurnPhase CurrentPhase = ETurnPhase::PlayerSelecting;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	TArray<FQueuedAction> PlayerActionQueue;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float MaxSelectionTime = 15.0f;

	float CurrentSelectionTime = 0.0f;
};
