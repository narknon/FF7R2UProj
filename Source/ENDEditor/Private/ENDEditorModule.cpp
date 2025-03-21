#include "ENDEditorModule.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_EffectAppendixMesh.h"
#include "AssetTypeActions_EndEmissiveColorSettings.h"
#include "AssetTypeActions_EndCinemaSequence.h"
#include "AssetTypeActions_EndCameraSequence.h"
#include "AssetTypeActions_EndDataObject.h"
#include "AssetTypeActions_ShaderResourceBuffer.h"
#include "AssetTypeActions_EndAssetPack.h"
#include "AssetTypeActions_EndAnimSet.h"
#include "EffectAppendixMesh.h"
#include "EditorFramework/AssetImportData.h"
#include "Editor.h"

const FName FENDEditorModule::DataObjectEditorAppIdentifier(TEXT("DataObjectEditorApp"));

// Add a tick delegate for animating EffectAppendixMesh assets
class FEffectAppendixMeshAnimationTicker
{
public:
    // Frame rate settings
    static constexpr float TargetFPS = 30.0f;
    static constexpr float FrameTime = 1.0f / TargetFPS;
    
    static bool Tick(float DeltaTime)
    {
        // Track accumulated time for throttling
        static float AccumulatedTime = 0.0f;
        static bool bNeedsRedraw = false;
        
        // Accumulate time
        AccumulatedTime += DeltaTime;
        
        // Only process updates at the target frame rate
        if (AccumulatedTime >= FrameTime)
        {
            // Store the time for updates
            float ActualDeltaTime = AccumulatedTime;
            AccumulatedTime = 0.0f; // Reset counter
            
            bNeedsRedraw = false; // Reset the flag
            
            // Process all loaded EffectAppendixMesh assets
            for (TObjectIterator<UEffectAppendixMesh> It; It; ++It)
            {
                UEffectAppendixMesh* EffectAppendixMesh = *It;
                if (EffectAppendixMesh && !EffectAppendixMesh->IsPendingKill())
                {
#if WITH_EDITOR
                    // Only tick if the animation is actually playing
                    if (EffectAppendixMesh->IsAnimationPlaying())
                    {
                        // Let the mesh handle its own timing and updates
                        EffectAppendixMesh->Tick(ActualDeltaTime);
                        
                        // Mark that we have active animations
                        bNeedsRedraw = true;
                    }
#endif
                }
            }
            
            // Only schedule a redraw if there's an active animation
            // and we're at the correct frame time
            if (bNeedsRedraw && GEditor)
            {
                // Don't actually redraw here - let the individual meshes handle it
                // This avoids redrawing multiple times in the same frame
            }
        }
        
        return true; // Keep ticking
    }
};


void FENDEditorModule::StartupModule()
{
    FAssetToolsModule& AssetToolsModule = FAssetToolsModule::GetModule();

	IAssetTools& AssetTools = AssetToolsModule.Get();
	
	EAssetTypeCategories::Type CustomAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName("SQEX"), FText::FromString("SQEX"));
	AssetAction = new FAssetTypeActions_EndEmissiveColorSettings(CustomAssetCategory);
	AssetAction2 = new FAssetTypeActions_EffectAppendixMesh(CustomAssetCategory);
	AssetAction3 = new FAssetTypeActions_EndCameraSequence(CustomAssetCategory);
	AssetAction4 = new FAssetTypeActions_EndCinemaSequence(CustomAssetCategory);
	AssetAction5 = new FAssetTypeActions_EndAnimSet(CustomAssetCategory);
	AssetAction6 = new FAssetTypeActions_EndAssetPack(CustomAssetCategory);
	AssetAction7 = new FAssetTypeActions_ShaderResourceBuffer(CustomAssetCategory);
    AssetAction8 = new FAssetTypeActions_EndDataObject(CustomAssetCategory);
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction));
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction2));
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction3));
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction4));
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction5));
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction6));
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction7));
    AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction8));

    // Register tick delegate for animating EffectAppendixMesh assets
    TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateStatic(&FEffectAppendixMeshAnimationTicker::Tick)
    );

    MenuExtensibilityManager = MakeShareable(new FExtensibilityManager);
    ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);
}

void FENDEditorModule::ShutdownModule()
{
	if (UObjectInitialized())
	{
		FAssetToolsModule& AssetToolsModule = FAssetToolsModule::GetModule();
		IAssetTools& AssetTools = AssetToolsModule.Get();
		AssetTools.UnregisterAssetTypeActions(AssetAction->AsShared());
		AssetTools.UnregisterAssetTypeActions(AssetAction2->AsShared());
		AssetTools.UnregisterAssetTypeActions(AssetAction3->AsShared());
		AssetTools.UnregisterAssetTypeActions(AssetAction4->AsShared());
		AssetTools.UnregisterAssetTypeActions(AssetAction5->AsShared());
		AssetTools.UnregisterAssetTypeActions(AssetAction6->AsShared());
		AssetTools.UnregisterAssetTypeActions(AssetAction7->AsShared());
        AssetTools.UnregisterAssetTypeActions(AssetAction8->AsShared());

        // Unregister tick delegate
        FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);

        MenuExtensibilityManager.Reset();
        ToolBarExtensibilityManager.Reset();
    }
}

IMPLEMENT_MODULE(FENDEditorModule, ENDEditor)