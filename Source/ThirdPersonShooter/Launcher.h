// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Launcher.generated.h"


UCLASS()
class THIRDPERSONSHOOTER_API ALauncher : public AWeapon
{
	GENERATED_BODY()
	
public:
	bool PullTrigger() override;
	void Reload() override;

	ALauncher();

protected:
	void BeginPlay() override;
};
