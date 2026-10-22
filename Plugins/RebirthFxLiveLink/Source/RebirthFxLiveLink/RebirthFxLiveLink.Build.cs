using UnrealBuildTool;

public class RebirthFxLiveLink : ModuleRules
{
    public RebirthFxLiveLink(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivateDependencyModuleNames.AddRange(new[] {
            "Core", "CoreUObject", "Engine", "UnrealEd", "Slate", "SlateCore", "EditorStyle", "InputCore", "DesktopPlatform",
            "RenderCore", "RHI", "Json"
        });
    }
}
