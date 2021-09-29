// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API AGun : public AWeapon
{
	GENERATED_BODY()

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool HitScanTrace(FHitResult &outHitInfo, FVector &outShotDirection);

};
