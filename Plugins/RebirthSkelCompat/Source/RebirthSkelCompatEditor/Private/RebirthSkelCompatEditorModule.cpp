// RebirthSkelCompat editor module: the data object, and the Move Maker tab (Window > Rebirth Move Maker).
#include "EndMoveMaker.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "Misc/CoreDelegates.h"
#include "Modules/ModuleManager.h"
#include "UObject/UObjectGlobals.h"
#include "ToolMenus.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "RebirthSkelCompatEditorModule"

class FRebirthSkelCompatEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(RebirthSkelCompatEditor::MoveMakerTabName, FOnSpawnTab::CreateStatic(&RebirthSkelCompatEditor::SpawnMoveMakerTab))
			.SetDisplayName(LOCTEXT("MoveMakerTab", "Rebirth Move Maker"))
			.SetTooltipText(LOCTEXT("MoveMakerTabTip", "Make a character's attacks, abilities and limit breaks from any animation (RebirthSkelCompat)."))
			.SetMenuType(ETabSpawnerMenuType::Hidden);
		UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FRebirthSkelCompatEditorModule::RegisterMenus));
		// 1.11.1: ACL's safety fallback off for the game's settings, in the editor and in the cooker (which compresses the
		// moves again): see TurnOffAclSafetyFallback
		PostEngineInit = FCoreDelegates::OnPostEngineInit.AddLambda([]() { RebirthSkelCompatEditor::TurnOffAclSafetyFallback(); });
		AssetLoaded = FCoreUObjectDelegates::OnAssetLoaded.AddStatic(&RebirthSkelCompatEditor::TurnOffAclSafetyFallbackOnLoad);
	}

	virtual void ShutdownModule() override
	{
		FCoreDelegates::OnPostEngineInit.Remove(PostEngineInit);
		FCoreUObjectDelegates::OnAssetLoaded.Remove(AssetLoaded);
		UToolMenus::UnRegisterStartupCallback(this);
		UToolMenus::UnregisterOwner(this);
		if (FSlateApplication::IsInitialized())
		{
			FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(RebirthSkelCompatEditor::MoveMakerTabName);
		}
	}

private:
	FDelegateHandle PostEngineInit;
	FDelegateHandle AssetLoaded;

	void RegisterMenus()
	{
		FToolMenuOwnerScoped Owner(this);
		if (UToolMenu* Menu = UToolMenus::Get()->ExtendMenu(TEXT("LevelEditor.MainMenu.Window")))
		{
			FToolMenuSection& Section = Menu->AddSection(TEXT("RebirthSkelCompat"), LOCTEXT("RebirthSection", "Rebirth"));
			Section.AddMenuEntry(TEXT("RebirthMoveMaker"), LOCTEXT("MoveMakerMenu", "Rebirth Move Maker"),
				LOCTEXT("MoveMakerMenuTip", "Make a character's attacks, abilities and limit breaks from any animation, with their hits, effects and sounds."),
				FSlateIcon(), FUIAction(FExecuteAction::CreateStatic(&FRebirthSkelCompatEditorModule::OpenMoveMaker)));
		}
	}

	static void OpenMoveMaker()
	{
		RebirthSkelCompatEditor::OpenMoveMakerTab(nullptr);
	}
};

IMPLEMENT_MODULE(FRebirthSkelCompatEditorModule, RebirthSkelCompatEditor)

#undef LOCTEXT_NAMESPACE
