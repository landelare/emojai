// Copyright © Laura Andelare, inspired by UEXTM::Xero from Unreal Slackers.
// This program is free software. It comes without any warranty, to the extent
// permitted by applicable law. You can redistribute it and/or modify it under
// the terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file for more details.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "EmojAISettings.generated.h"

UCLASS(Config = "Game", Defaultconfig, Meta = (DisplayName = "EmojAI",
	ToolTip = "Settings for the EmojAI plugin"))
class EMOJAI_API UEmojAISettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "UI")
	TSoftObjectPtr<class UMaterialInterface> WidgetMaterial;

	UPROPERTY(Config, EditAnywhere, Category = "UI")
	int32 FontSize = 36;

	UPROPERTY(Config, EditAnywhere, Category = "UI")
	FVector2D DrawSize = {400, 60};

	UEmojAISettings();
};
