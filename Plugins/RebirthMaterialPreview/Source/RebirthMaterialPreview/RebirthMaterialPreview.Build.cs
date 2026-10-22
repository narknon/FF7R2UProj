using System.IO;
using UnrealBuildTool;

public class RebirthMaterialPreview : ModuleRules
{
    public RebirthMaterialPreview(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivateDependencyModuleNames.AddRange(new[] {
            "Core", "CoreUObject", "Engine", "UnrealEd", "AssetTools", "AssetRegistry",
            "Slate", "SlateCore", "ContentBrowser", "InputCore", "EditorStyle", "ToolMenus", "Niagara", "NiagaraCore",
            "RenderCore", "RHI", "Json", "JsonUtilities", "EndDataObject", "DesktopPlatform", "TargetPlatform", "PropertyEditor", "BonamikRt", "Persona", "AdvancedPreviewScene", "AnimationEditor", "SkeletonEditor", "SkeletalMeshEditor", "AnimGraph", "AnimGraphRuntime", "Kismet", "RebirthSafeLoad"
        });

        // RebirthEngineV5's UE4Editor-Engine.dll exports engine additions (RebirthSkeletonCompatibility) that its
        // UE4Editor-Engine.lib predates. Tools\EndEditorPlugins\build_editor_plugins.py makes this import library
        // from the DLL's own export table; link it when it is there.
        string RebirthEngineExports = Path.Combine(ModuleDirectory, "ThirdParty", "RebirthEngineExports.lib");
        if (File.Exists(RebirthEngineExports))
        {
            PublicAdditionalLibraries.Add(RebirthEngineExports);
        }
    }
}
