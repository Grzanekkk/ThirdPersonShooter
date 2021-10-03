// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPSCharacter.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Nameplate.generated.h"


UCLASS(Abstract)
class THIRDPERSONSHOOTER_API UNameplate : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void SetOwner(ATPSCharacter* ACharacter);

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	ATPSCharacter* OwnerCharacter;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentHealthLabel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MaxHealthLabel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* NameLabel;
};
