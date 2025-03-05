// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "HSFLipSyncEditorEdMode.h"
#include "HSFLipSyncEditorEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FHSFLipSyncEditorEdMode::EM_HSFLipSyncEditorEdModeId = TEXT("EM_HSFLipSyncEditorEdMode");

FHSFLipSyncEditorEdMode::FHSFLipSyncEditorEdMode()
{

}

FHSFLipSyncEditorEdMode::~FHSFLipSyncEditorEdMode()
{

}

void FHSFLipSyncEditorEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FHSFLipSyncEditorEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FHSFLipSyncEditorEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FHSFLipSyncEditorEdMode::UsesToolkits() const
{
	return true;
}




