// Copyright © Laura Andelare, inspired by UEXTM::Xero from Unreal Slackers.
// This program is free software. It comes without any warranty, to the extent
// permitted by applicable law. You can redistribute it and/or modify it under
// the terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file for more details.

#include "EmojAIDisplayComponent.h"
#include "Materials/Material.h"
#include "UObject/ConstructorHelpers.h"
#include "Widgets/Text/STextBlock.h"

UEmojAIDisplayComponent::UEmojAIDisplayComponent()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFinder(
		TEXT("Material'/EmojAI/M_Widget_Passthrough.M_Widget_Passthrough'"));
	MaskedMaterial = MaterialFinder.Object;
	bIsTwoSided = true;

	SetAbsolute(false, true, false); // Detach rotation
	SetCastShadow(false);
	SetWidgetSpace(EWidgetSpace::World);
	SetDrawSize(FVector2D(400, 60));
}

void UEmojAIDisplayComponent::BeginPlay()
{
	Super::BeginPlay();

	TextBlock = SNew(STextBlock);
	FSlateFontInfo FontInfo = FCoreStyle::GetDefaultFontStyle("Regular", FontSize);
	TextBlock->SetFont(FontInfo);
	TextBlock->SetJustification(ETextJustify::Center);
	SetSlateWidget(TextBlock);

	// Force update in case something else already added something.
	UpdateText();
}

UMaterialInterface* UEmojAIDisplayComponent::GetMaterial(int32 MaterialIndex) const
{
	return MaskedMaterial;
}

void UEmojAIDisplayComponent::Set(FString State)
{
	Stack.Empty();
	Stack.Add(MoveTemp(State));
	UpdateText();
}

void UEmojAIDisplayComponent::Push(FString State)
{
	Stack.Add(MoveTemp(State));
	UpdateText();
}

void UEmojAIDisplayComponent::Pop()
{
	Stack.Pop();
	UpdateText();
}

void UEmojAIDisplayComponent::Clear()
{
	Stack.Empty();
	UpdateText();
}

void UEmojAIDisplayComponent::UpdateText()
{
	if (!TextBlock)
		return;

	FString Text = FString::Join(Stack, TEXT("|"));
	TextBlock->SetText(FText::AsCultureInvariant(MoveTemp(Text)));
}
