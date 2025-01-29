using UnrealBuildTool;

public class EndGame : ModuleRules {
    public EndGame(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        ShadowVariableWarningLevel = WarningLevel.Warning;
        
        PublicDependencyModuleNames.AddRange(new string[] {
            "AIModule",
            "AnimGraphRuntime",
            "AnimationBudgetAllocator",
            "AnimationCore",
            "BodyDriverPlugin",
            "BonamikRt",
            "CinematicCamera",
            "ControlRig",
            "Core",
            "CoreUObject",
            "EndCore",
            "EndDataBase",
            "EndDataObject",
            "EndOneSaveData",
            "Engine",
            "GameplayTasks",
            "HSFLipSyncRuntime",
            "InputCore",
            "KBDRt",
            "LevelSequence",
            "MediaAssets",
            "MovieScene",
            "MovieSceneTracks",
            "NavigationSystem",
            "Niagara",
            "NiagaraCore",
            "NiagaraAnimNotifies",
            "Paper2D",
            "PhysXVehicles",
            "PhysicsCore",
            "RenderCore",
            "RigVM",
            "SQEXSEAD",
            "Slate",
            "SlateCore",
            "UMG",
            "VFXNiagara",
        });
    }
}
