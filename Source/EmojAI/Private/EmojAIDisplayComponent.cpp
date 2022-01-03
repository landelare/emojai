// Copyright © Laura Andelare, inspired by UEXTM::Xero from Unreal Slackers.
// This program is free software. It comes without any warranty, to the extent
// permitted by applicable law. You can redistribute it and/or modify it under
// the terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file for more details.

#include "EmojAIDisplayComponent.h"
#include "EmojAISettings.h"
#include "Widgets/Text/STextBlock.h"

UEmojAIDisplayComponent::UEmojAIDisplayComponent()
{
	bIsTwoSided = true;

	SetAbsolute(false, true, false); // Detach rotation
	SetCastShadow(false);
	SetWidgetSpace(EWidgetSpace::World);

	auto* Settings = GetDefault<UEmojAISettings>();
	FontSize = Settings->FontSize;
	SetDrawSize(Settings->DrawSize);

#if WITH_EDITOR
	auto& Delegate = GetMutableDefault<UEmojAISettings>()->OnSettingChanged();
	Delegate.AddUObject(this, &ThisClass::OnSettingChanged);
#endif
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
	// Deliberately not calling Super, this condition mimics what it does
	if (OverrideMaterials.IsValidIndex(MaterialIndex) &&
	    OverrideMaterials[MaterialIndex])
		return OverrideMaterials[MaterialIndex];

	return GetDefault<UEmojAISettings>()->WidgetMaterial.LoadSynchronous();
}

#if WITH_EDITOR
bool UEmojAIDisplayComponent::CanEditChange(const FProperty* InProperty) const
{
	FName PropertyName = InProperty->GetFName();

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, FontSize))
		return !bUseDefaultFontSize;

	// This is defined in UWidgetComponent but it only compiles with ThisClass
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, DrawSize))
		return !bUseDefaultDrawSize;

	return Super::CanEditChange(InProperty);
}

void UEmojAIDisplayComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	OnSettingChanged(GetMutableDefault<UEmojAISettings>(), PropertyChangedEvent);
}
#endif

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

#if WITH_EDITOR
void UEmojAIDisplayComponent::OnSettingChanged(
	UObject* SettingsObject, FPropertyChangedEvent& PropertyChangedEvent)
{
	auto* Settings = CastChecked<UEmojAISettings>(SettingsObject);

	if (bUseDefaultFontSize)
		FontSize = Settings->FontSize;

	if (bUseDefaultDrawSize)
	{
		SetDrawSize(Settings->DrawSize);
		UpdateWidget();
	}

	if (TextBlock)
	{
		FSlateFontInfo FontInfo = FCoreStyle::GetDefaultFontStyle("Regular", FontSize);
		TextBlock->SetFont(FontInfo);
		UpdateText();
	}
}
#endif
