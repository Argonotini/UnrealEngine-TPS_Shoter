// Shooter Game. By xDedic. All Rights reserved.

using UnrealBuildTool;

public class Artriam : ModuleRules
{
	public Artriam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Niagara",
			"PhysicsCore",
			"GameplayTasks",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] 
		{ 
			"Artriam/Public/Player",
			"Artriam/Public/Components",
			"Artriam/Public/Dev",
			"Artriam/Public/Weapon",
			"Artriam/Public/UI",
			"Artriam/Public/Animations",
			"Artriam/Public/Pickups",
			"Artriam/Public/Weapon/Components",
			"Artriam/Public/AI",
			"Artriam/Public/AI/Tasks",
			"Artriam/Public/AI/Services",
			"Artriam/Public/AI/EQS",
			"Artriam/Public/AI/Decorators",
			"Artriam/Public/Menu",
			"Artriam/Public/Menu/UI",
			"Artriam/Public/Sound",
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
