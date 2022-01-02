// Copyright © Laura Andelare, inspired by UEXTM::Xero from Unreal Slackers.
// This program is free software. It comes without any warranty, to the extent
// permitted by applicable law. You can redistribute it and/or modify it under
// the terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file for more details.

#pragma once

#include "Components/WidgetComponent.h"
#include "EmojAIDisplayComponent.generated.h"

/**
 * World-space widget component with a convenient API to show the current
 * status of various actors.
 */
UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent,
	DisplayName = "EmojAI Display"))
class EMOJAI_API UEmojAIDisplayComponent : public UWidgetComponent
{
	GENERATED_BODY()

	TArray<FString> Stack;
	TSharedPtr<class STextBlock> TextBlock;

public:
	UPROPERTY(EditAnywhere, Category = "EmojAI Display")
	int32 FontSize;

	UEmojAIDisplayComponent();

	virtual void BeginPlay() override;
	virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;

	/**
	 * Replaces what's displayed with the provided string.
	 * Useful for debugging scalar states.
	 */
	UFUNCTION(BlueprintCallable, Category = "EmojAI Display",
		DisplayName = "Set State", Meta = (DevelopmentOnly))
	void Set(FString State);

	/**
	 * Adds a section of text to what's displayed, separated by |.
	 * Useful for debugging stack/tree-like states like a behavior tree.
	 */
	UFUNCTION(BlueprintCallable, Category = "EmojAI Display",
		DisplayName = "Push State", Meta = (DevelopmentOnly))
	void Push(FString State);

	/**
	 * Removes the last string that was Pushed (or the only one that was Set).
	 */
	UFUNCTION(BlueprintCallable, Category = "EmojAI Display",
		DisplayName = "Pop State", Meta = (DevelopmentOnly))
	void Pop();

	/**
	 * Removes all state Pushed or Set.
	 */
	UFUNCTION(BlueprintCallable, Category = "EmojAI Display",
		DisplayName = "Clear State", Meta = (DevelopmentOnly))
	void Clear();

private:
	void UpdateText();
};
