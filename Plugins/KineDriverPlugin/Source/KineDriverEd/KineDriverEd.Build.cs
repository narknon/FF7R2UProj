using UnrealBuildTool;

public class KineDriverEd : ModuleRules {
    public KineDriverEd(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        ShadowVariableWarningLevel = WarningLevel.Warning;
        
        PublicDependencyModuleNames.AddRange(new string[] {
            "AnimGraphRuntime",
            "Core",
            "CoreUObject",
            "DeveloperSettings",
            "Engine",
            "UnrealEd",
            "KineDriverRt",
        });
    }
}
