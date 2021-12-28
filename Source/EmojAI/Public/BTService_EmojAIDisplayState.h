// Copyright © Laura Andelare, inspired by UEXTM::Xero from Unreal Slackers.
// This program is free software. It comes without any warranty, to the extent
// permitted by applicable law. You can redistribute it and/or modify it under
// the terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file for more details.

#pragma once

#include "EmojAIDisplayComponent.h"
#include "BehaviorTree/BTService.h"
#include "BTService_EmojAIDisplayState.generated.h"

UCLASS(HideCategories = ("Service"))
class EMOJAI_API UBTService_EmojAIDisplayState : public UBTService
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "EmojAI")
	FString Text;

public:
	UBTService_EmojAIDisplayState();
	virtual FString GetStaticDescription() const override;

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp,
	                              uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp,
	                             uint8* NodeMemory) override;

private:
	static UEmojAIDisplayComponent* GetDisplayComponent(
		const UBehaviorTreeComponent&);
};
