// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Sorelle_summer23 : ModuleRules
{
	public Sorelle_summer23(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
