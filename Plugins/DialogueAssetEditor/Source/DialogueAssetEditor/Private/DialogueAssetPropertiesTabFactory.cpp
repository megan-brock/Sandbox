#include "DialogueAssetPropertiesTabFactory.h"
#include "DialogueAssetEditorApp.h"
#include "DialogueAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "Widgets/Text/STextBlock.h"
#include "DialogueNodeInfo.h"

DialogueAssetPropertiesTabFactory::DialogueAssetPropertiesTabFactory(TSharedPtr<class DialogueAssetEditorApp> app) : FWorkflowTabFactory(FName("DialogueAssetPropertiesTab"), app)
{
	App = app;
	TabLabel = FText::FromString(TEXT("Properties"));
	ViewMenuDescription = FText::FromString(TEXT("Displays properties view for the current asset."));
	ViewMenuTooltip = FText::FromString(TEXT("Show the properties view."));
}
	
TSharedRef<SWidget> DialogueAssetPropertiesTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedPtr<DialogueAssetEditorApp> app = App.Pin();
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
	
	FDetailsViewArgs detailsViewArgs;
	{
		detailsViewArgs.bAllowSearch = false;
		detailsViewArgs.bHideSelectionTip = true;
		detailsViewArgs.bLockable = false;
		detailsViewArgs.bSearchInitialKeyFocus = true;
		detailsViewArgs.bUpdatesFromSelection = false;
		detailsViewArgs.NotifyHook = nullptr;
		detailsViewArgs.bShowOptions = true;
		detailsViewArgs.bShowModifiedPropertiesOption = false;
		detailsViewArgs.bShowScrollBar = false;
	}
	
	TSharedPtr<IDetailsView> detailsView = PropertyEditorModule.CreateDetailView(detailsViewArgs);
	detailsView->SetObject(app->GetWorkingAsset());
	
	TSharedPtr<IDetailsView> selectedNodeDetailsView = PropertyEditorModule.CreateDetailView(detailsViewArgs);
	selectedNodeDetailsView->SetObject(nullptr);
	app->SetSelectedNodeDetailsView(selectedNodeDetailsView);
	
	return SNew(SVerticalBox) 
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(HAlign_Fill)
		[
			detailsView.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(HAlign_Fill)
		[
			selectedNodeDetailsView.ToSharedRef()
		];
}

FText DialogueAssetPropertiesTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("A properties view for the current asset."));
}
