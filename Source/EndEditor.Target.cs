using UnrealBuildTool;

public class EndEditorTarget : TargetRules {
	public EndEditorTarget(TargetInfo Target) : base(Target) {
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new string[] {
			"EndCore",
			"EndDataBase",
			"EndDataObject",
			"EndDebug",
            "ENDEditor",
			"EndGame",
			"EndOneSaveData",
		});
	}
}
