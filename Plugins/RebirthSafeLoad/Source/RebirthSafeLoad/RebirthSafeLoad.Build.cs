using UnrealBuildTool;

public class RebirthSafeLoad : ModuleRules
{
    public RebirthSafeLoad(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivateDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject" });
    }
}
