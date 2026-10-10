// Copyright Epic Games, Inc. All Rights Reserved.

#include "DialogueAssetEditor.h"
#include "DialogueAssetAction.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "DialogueGraphNode.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"
#include "EdGraphUtilities.h"
#include "KismetPins/SGraphPinColor.h"
#include "EdGraph/EdGraphPin.h"
#include "DialogueNodeInfoDetailsCustomization.h"
#include "SpeakerAssetAction.h"
#include "PropertyEditorModule.h"
#include "SGraphNodeDialogue.h"

#define LOCTEXT_NAMESPACE "FDialogueAssetEditorModule"

class SDialogueStartGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueStartGraphPin) {}
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}
	
protected:
	virtual FSlateColor GetPinColor() const override
	{
		return FSlateColor(FLinearColor(1.0f, 0.2f, 0.6f));
	}
};

struct FDialoguePinFactory : public FGraphPanelPinFactory
{
public:
	virtual ~FDialoguePinFactory() override {}
	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* InGraphPinObj) const override
	{
		if (FName(TEXT("DialoguePin")) == InGraphPinObj->PinType.PinSubCategory)
		{
			return SNew(SDialoguePin, InGraphPinObj);
		}
		if (FName(TEXT("StartPin")) == InGraphPinObj->PinType.PinSubCategory)
		{
			return SNew(SDialogueStartGraphPin, InGraphPinObj);
		}
		
		return nullptr;
	}
};

struct FDialogueNodeFactory : public FGraphPanelNodeFactory
{
public:
	virtual ~FDialogueNodeFactory() override {}
	virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* InNode) const override
	{
		if (UDialogueGraphNode* DialogueNode = Cast<UDialogueGraphNode>(InNode))
		{
			return SNew(SGraphNodeDialogue, InNode);
		}
		return nullptr;
	}
};

void FDialogueAssetEditorModule::StartupModule()
{
	IAssetTools& assetToolsModule = IAssetTools::Get();
	EAssetTypeCategories::Type assetType = assetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("DialogueAssets")), FText::FromString("Dialogue Assets"));
	TSharedPtr<DialogueAssetAction> dialogueAssetAction = MakeShareable(new DialogueAssetAction(assetType));
	TSharedPtr<SpeakerAssetAction> speakerAssetAction = MakeShareable(new SpeakerAssetAction(assetType));

	assetToolsModule.RegisterAssetTypeActions(dialogueAssetAction.ToSharedRef());
	assetToolsModule.RegisterAssetTypeActions(speakerAssetAction.ToSharedRef());
	
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
	PropertyEditorModule.RegisterCustomClassLayout(
		TEXT("DialogueNodeInfo"),
		FOnGetDetailCustomizationInstance::CreateStatic(&FDialogueNodeInfoDetailsCustomization::MakeInstance)
	);
	PropertyEditorModule.NotifyCustomizationModuleChanged();
	
	StyleSet = MakeShareable(new FSlateStyleSet(TEXT("DialogueAssetEditorStyle")));
	TSharedPtr<IPlugin> plugin = IPluginManager::Get().FindPlugin(TEXT("DialogueAssetEditor"));
	FString contentDir = plugin->GetContentDir();
	StyleSet->SetContentRoot(contentDir);
	
	FSlateImageBrush* thumbnailBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("DialogueAssetThumbnail"), TEXT(".png")), FVector2D(128.0, 128.0));
	FSlateImageBrush* iconBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("DialogueAssetIcon"), TEXT(".png")), FVector2D(128.0, 128.0));
	
	StyleSet->Set(TEXT("ClassThumbnail.DialogueAsset"), thumbnailBrush);
	StyleSet->Set(TEXT("ClassIcon.DialogueAsset"), iconBrush);
	
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
	
	PinFactory = MakeShareable(new FDialoguePinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(PinFactory);
	
	NodeFactory = MakeShareable(new FDialogueNodeFactory());
	FEdGraphUtilities::RegisterVisualNodeFactory(NodeFactory);
}

void FDialogueAssetEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded(TEXT("PropertyEditor")))
	{
		FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
		PropertyEditorModule.UnregisterCustomClassLayout(TEXT("DialogueNodeInfo"));
		PropertyEditorModule.NotifyCustomizationModuleChanged();
	}
	
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
	if (PinFactory.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualPinFactory(PinFactory);
	}
	if (NodeFactory.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualNodeFactory(NodeFactory);
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogueAssetEditorModule, DialogueAssetEditor)