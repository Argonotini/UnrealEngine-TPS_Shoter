// Shooter Game. By xDedic. All Rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ArtriamTarget : TargetRules
{
	public ArtriamTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Artriam" } );
	}
}
