// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestDediServer : ModuleRules
{
	public TestDediServer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Networking", "Sockets" });
	}
}
