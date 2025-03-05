using UnrealBuildTool;

public class BonamikEd : ModuleRules {
    public BonamikEd(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        ShadowVariableWarningLevel = WarningLevel.Warning;
        
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "BonamikRt",
            "UnrealEd",
            "DeveloperSettings",
        });
    }
}