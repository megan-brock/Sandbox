#include "DialogueAssetAppMode.h"
#include "DialogueAssetEditorApp.h"
#include "DialogueAssetPrimaryTabFactory.h"
#include "DialogueAssetPropertiesTabFactory.h"

DialogueAssetAppMode::DialogueAssetAppMode(TSharedPtr<class DialogueAssetEditorApp> app) : FApplicationMode(TEXT("DialogueAssetAppMode"))
{
	App = app;
	AllowedTabs.RegisterFactory(MakeShareable(new DialogueAssetPrimaryTabFactory(app)));
	AllowedTabs.RegisterFactory(MakeShareable(new DialogueAssetPropertiesTabFactory(app)));
	
	TabLayout = FTabManager::NewLayout("DialogueAssetAppMode_Layout_v1")
	->AddArea
	(
		FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split(
				FTabManager::NewSplitter()
					->SetOrientation(Orient_Horizontal)
					->Split
					(
						FTabManager::NewStack()
							->SetSizeCoefficient(0.75f)
							->AddTab(FName(TEXT("DialogueAssetPrimaryTab")), ETabState::OpenedTab)
					)
					->Split
					(
					FTabManager::NewStack()
						->SetSizeCoefficient(0.25f)
						->AddTab(FName(TEXT("DialogueAssetPropertiesTab")), ETabState::OpenedTab)
					)
			)
	);
}

void DialogueAssetAppMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	TSharedPtr<DialogueAssetEditorApp> app = App.Pin();
	app->PushTabFactories(AllowedTabs);
	FApplicationMode::RegisterTabFactories(InTabManager);
}

void DialogueAssetAppMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void DialogueAssetAppMode::PostActivateMode()
{
	FApplicationMode::PostActivateMode();
}