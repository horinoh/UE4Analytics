// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class UE4Analytics : ModuleRules
{
	public UE4Analytics(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore"
        , "Analytics" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PrivatePCHHeaderFile = "UE4Analytics.h";

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
