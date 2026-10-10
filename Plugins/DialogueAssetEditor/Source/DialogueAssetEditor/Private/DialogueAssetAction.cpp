#include "DialogueAssetAction.h"
#include "DialogueAsset.h"
#include "DialogueAssetEditorApp.h"

DialogueAssetAction::DialogueAssetAction(EAssetTypeCategories::Type Category)
{
	AssetCategory = Category;
}

FText DialogueAssetAction::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_DialogueAsset", "Dialogue Asset");
}

FColor DialogueAssetAction::GetTypeColor() const
{
	return FColor::Green;
}

UClass* DialogueAssetAction::GetSupportedClass() const
{
	return UDialogueAsset::StaticClass();
}

uint32 DialogueAssetAction::GetCategories()
{
	return AssetCategory;
}

void DialogueAssetAction::OpenAssetEditor(const TArray<UObject*>& inObjects, TSharedPtr<class IToolkitHost> editWithinLevelEditor)
{
	EToolkitMode::Type Mode = editWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (UObject* object : inObjects)
	{
		UDialogueAsset* dialogueAsset = Cast<UDialogueAsset>(object);
		if (dialogueAsset != nullptr)
		{
			TSharedRef<DialogueAssetEditorApp> editor(new DialogueAssetEditorApp());
			editor->InitEditor(Mode, editWithinLevelEditor, dialogueAsset);
		}
	}
}