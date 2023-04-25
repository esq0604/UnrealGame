// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RetargetingTest : ModuleRules
{
	public RetargetingTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput","UMG","GameplayTags","MotionWarping","GameplayAbilities", "GameplayTasks" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate","SlateCore" });

	}
}
