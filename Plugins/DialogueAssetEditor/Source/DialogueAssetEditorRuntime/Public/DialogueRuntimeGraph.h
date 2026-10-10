#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfoBase.h"
#include "DialogueNodeType.h"
#include "UObject/NameTypes.h"
#include "DialogueRuntimeGraph.generated.h"

UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UDialogueRuntimePin : public UObject
{
	GENERATED_BODY()
	
public:
	FName PinName;
	
	UPROPERTY()
	FGuid PinId;
	
	UPROPERTY()
	TArray<UDialogueRuntimePin*> Connections;
	
	UPROPERTY()
	class UDialogueRuntimeNode* Parent = nullptr;
};

UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UDialogueRuntimeNode : public UObject
{
	GENERATED_BODY()
	
public:
	EDialogueNodeType NodeType = EDialogueNodeType::DialogueNode;
	
	UPROPERTY()
	UDialogueRuntimePin* InputPin = nullptr;
	
	UPROPERTY()
	TArray<UDialogueRuntimePin*> OutputPins;
	
	UPROPERTY()
	FVector2D Position;
	
	UPROPERTY()
	UDialogueNodeInfoBase* NodeInfo = nullptr;
};

UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UDialogueRuntimeGraph : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<UDialogueRuntimeNode*> Nodes;
};