// Copyright © Laura Andelare, inspired by UEXTM::Xero from Unreal Slackers.
// This program is free software. It comes without any warranty, to the extent
// permitted by applicable law. You can redistribute it and/or modify it under
// the terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file for more details.

using UnrealBuildTool;

public class EmojAI : ModuleRules
{
    public EmojAI(ReadOnlyTargetRules Target)
        : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new[]
        {
            "AIModule",
            "Core",
            "CoreUObject",
            "Engine",
            "GameplayTasks",
            "Slate",
            "SlateCore",
            "UMG",
        });
    }
}
