using UnrealBuildTool;

public class EndTarget : TargetRules {
	public EndTarget(TargetInfo Target) : base(Target) {
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new string[] {
			"EndCore",
			"EndDataBase",
			"EndDataObject",
			"EndDebug",
			"EndGame",
			"EndOneSaveData",
		});
	}
}
