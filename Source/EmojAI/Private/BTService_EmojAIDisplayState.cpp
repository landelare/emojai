// Copyright © Laura Andelare, inspired by UEXTM::Xero from Unreal Slackers.
// This program is free software. It comes without any warranty, to the extent
// permitted by applicable law. You can redistribute it and/or modify it under
// the terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file for more details.

#include "BTService_EmojAIDisplayState.h"
#include "AIController.h"

UBTService_EmojAIDisplayState::UBTService_EmojAIDisplayState()
{
	// It looks distracting in a BT if this has a name
	NodeName = TEXT(" ");

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
	bNotifyTick = false;
}

FString UBTService_EmojAIDisplayState::GetStaticDescription() const
{
	FStringFormatOrderedArguments Args;
	Args.Add(Text);
	return FString::Format(TEXT("State: {0}"), Args);
}

void UBTService_EmojAIDisplayState::OnBecomeRelevant(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	if (auto* Component = GetDisplayComponent(OwnerComp))
		Component->Push(Text);
}

void UBTService_EmojAIDisplayState::OnCeaseRelevant(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	if (auto* Component = GetDisplayComponent(OwnerComp))
		Component->Pop();
}

UEmojAIDisplayComponent* UBTService_EmojAIDisplayState::GetDisplayComponent(
	const UBehaviorTreeComponent& Component)
{
	if (auto* Controller = Cast<AAIController>(Component.GetOwner()))
		if (auto* Pawn = Controller->GetPawn())
			return Pawn->FindComponentByClass<UEmojAIDisplayComponent>();

	return nullptr;
}
