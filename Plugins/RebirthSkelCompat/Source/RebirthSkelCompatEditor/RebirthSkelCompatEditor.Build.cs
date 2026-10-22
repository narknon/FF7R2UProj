using UnrealBuildTool;

public class RebirthSkelCompatEditor : ModuleRules
{
    public RebirthSkelCompatEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        // SkelCompatCore.hpp (the game mod's own rules, shared so Validate shows what the game does) needs C++17.
        CppStandard = CppStandardVersion.Cpp17;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "UnrealEd",
            "BlueprintGraph",
            "AssetRegistry",
            "AssetTools",
            "Json",
            "InputCore",
            "Slate",
            "SlateCore",
            "EditorStyle",
            // Move Maker (editor 1.8): its details panel and its Window menu entry.
            "PropertyEditor",
            "ToolMenus",
            // (1.12.4) the game's effect parameters this editor cannot write, left out of copied effects (UnwritableNiagara).
            "Niagara",
            // (1.13.1) Flatten Root: RemoveBoneAnimation (UAnimationBlueprintLibrary) to rename a bone's track.
            "AnimationModifiers",
            // (1.13.1) Cook For Game: the WindowsNoEditor target platform.
            "TargetPlatform",
        });
    }
}
