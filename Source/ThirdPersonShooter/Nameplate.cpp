// Fill out your copyright notice in the Description page of Project Settings.


#include "Nameplate.h"

#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>

void UNameplate::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (OwnerCharacter != nullptr)
	{
		HealthBar->SetPercent(OwnerCharacter->GetHealthPercent());
		CurrentHealthLabel->SetText(FText::AsNumber(OwnerCharacter->GetHealth()));
		MaxHealthLabel->SetText(FText::AsNumber(OwnerCharacter->GetMaxHealth()));
		NameLabel->SetText(FText::FromString(OwnerCharacter->GetName()));
	}
}

void UNameplate::SetOwner(ATPSCharacter* ACharacter)
{
	OwnerCharacter = ACharacter;
}