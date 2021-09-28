// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API AGun : public AActor
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

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
		UParticleSystem* BulletImpact;

	UPROPERTY(EditAnywhere)
		float MaxRange = 10000;

	UPROPERTY(EditAnywhere)
		float Damage = 20;

	bool HitScanTrace(FHitResult &outHitInfo, FVector &outShotDirection);
	AController* GetOwnerController() const;
};
