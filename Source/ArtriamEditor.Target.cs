// Shooter Game. By xDedic. All Rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ArtriamEditorTarget : TargetRules
{
	public ArtriamEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Artriam" } );
	}
}
