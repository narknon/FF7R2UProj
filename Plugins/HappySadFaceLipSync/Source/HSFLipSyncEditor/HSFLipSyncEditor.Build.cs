// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class HSFLipSyncEditor : ModuleRules
{
	public HSFLipSyncEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"HSFLipSyncEditor/Public",
				// ... add public include paths required here ...
            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"HSFLipSyncEditor/Private",
				// ... add other private include paths required here ...
            }
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
				"UnrealEd",
                "HSFLipSyncRuntime",
				"Json", // For JSON handling
				"JsonUtilities", // For JSON utilities
				"DesktopPlatform", // Add this line
				"AssetRegistry",
                "EditorScriptingUtilities"
            }
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"InputCore",
				"UnrealEd",
				"LevelEditor",
				"EditorScriptingUtilities", // Add this
				"EditorStyle",         // Editor styles and icons
				// ... add private dependencies that you statically link with here ...	
				"InputCore",
                "UnrealEd",
                "ToolMenus",
                "EditorWidgets",         // For widgets like SObjectPropertyEntryBox
				"PropertyEditor",        // Required for property-related widgets
				"AssetRegistry"
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
