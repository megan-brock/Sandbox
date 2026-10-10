#include "DialogueAssetPrimaryTabFactory.h"
#include "DialogueAssetEditorApp.h"
#include "DialogueAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "Widgets/Text/STextBlock.h"
#include "GraphEditor.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"

DialogueAssetPrimaryTabFactory::DialogueAssetPrimaryTabFactory(TSharedPtr<class DialogueAssetEditorApp> app) : FWorkflowTabFactory(FName("DialogueAssetPrimaryTab"), app)
{
	App = app;
	TabLabel = FText::FromString(TEXT("Primary"));
	ViewMenuDescription = FText::FromString(TEXT("Displays primary view"));
	ViewMenuTooltip = FText::FromString(TEXT("Show the primary view"));
}
	
TSharedRef<SWidget> DialogueAssetPrimaryTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedPtr<DialogueAssetEditorApp> app = App.Pin();

	SGraphEditor::FGraphEditorEvents graphEvents;
	graphEvents.OnSelectionChanged.BindRaw(app.Get(), &DialogueAssetEditorApp::OnGraphSelectionChanged);
	
	TSharedPtr<SGraphEditor> graphEditor = 
		SNew(SGraphEditor)
			.IsEditable(true)
			.GraphEvents(graphEvents)
			.GraphToEdit(app->GetWorkingGraph());
	
	app->SetWorkingGraphUi(graphEditor);
	
	return SNew(SVerticalBox) 
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(HAlign_Fill)
		[
			graphEditor.ToSharedRef()
		];
}

FText DialogueAssetPrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("A primary view for dialogue assets"));
}
