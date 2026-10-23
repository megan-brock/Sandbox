#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"
#include "SGraphPanel.h"

class DialogueAssetEditorApp : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{
public:
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& tabManager) override;
	void InitEditor(const EToolkitMode::Type mode, const TSharedPtr<IToolkitHost>& initToolkitHost, UObject* inObject);
	
	class UDialogueAsset* GetWorkingAsset() { return WorkingAsset; }
	class UEdGraph* GetWorkingGraph() { return WorkingGraph; }
	
	void SetWorkingGraphUi(TSharedPtr<class SGraphEditor> workingGraphUi) { WorkingGraphUi = workingGraphUi; }
	void SetSelectedNodeDetailsView(TSharedPtr<class IDetailsView> detailsView);
	void OnGraphSelectionChanged(const FGraphPanelSelectionSet& selection);
	
public:
	// FAssetEditorToolKit interface
	virtual FName GetToolkitFName() const override { return FName(TEXT("DialogueAssetEditorApp"));}
	virtual FText GetBaseToolkitName() const override { return FText::FromString(TEXT("DialogueAssetEditorApp")); }
	virtual FString GetWorldCentricTabPrefix() const override { return TEXT("DialogueAssetEditorApp"); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f); }
	virtual FString GetDocumentationLink() const override { return TEXT("https://github.com/megan-brock"); }
	virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override {}
	virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override {}
	// FAssetEditorToolKit interface
	
	virtual void OnClose() override;
	void OnNodeDetailViewPropertiesUpdated(const FPropertyChangedEvent& event);
	void OnWorkingAssetPreSave();
	
protected:
	void UpdateWorkingAssetFromGraph();
	void UpdateEditorGraphFromWorkingAsset();
	class UDialogueGraphNodeBase* GetSelectedNode(const FGraphPanelSelectionSet& selection) const;
	
private:
	class UDialogueAsset* WorkingAsset = nullptr;
	class UEdGraph* WorkingGraph = nullptr;

	TSharedPtr<class SGraphEditor> WorkingGraphUi = nullptr;
	TSharedPtr<class IDetailsView> SelectedNodeDetailsView = nullptr;
};
