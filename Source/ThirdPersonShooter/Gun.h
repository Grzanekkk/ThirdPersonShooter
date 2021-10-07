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

	bool PullTrigger() override;
	void Reload() override;

	void SpawnBulletHole(FVector Location, FRotator Rotation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool HitScanTrace(FHitResult &outHitInfo, FVector &outShotDirection);

	UPROPERTY(EditAnywhere)
		UMaterialInterface* BulletHoleMaterial;

private:
	FVector BulletHoleSize = FVector(10.0f, 10.0f, 50.0f);
};
