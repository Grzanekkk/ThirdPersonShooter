// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimerManager.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	virtual bool PullTrigger();
	virtual void Reload();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AController* GetOwnerController() const;

private:
	void ReloadAfterDelay();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
		UParticleSystem* BulletImpact;

	UPROPERTY(EditAnywhere)
		USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
		USoundBase* TerrainImpactSound;

	UPROPERTY(EditAnywhere)
		USoundBase* EnemyImpactSound;

	UPROPERTY(EditAnywhere)
		USoundBase* ReloadSound;

	UPROPERTY(EditAnywhere)
		USoundBase* EmptyMagSound;

	UPROPERTY(EditAnywhere)
		float MaxRange = 10000;

	UPROPERTY(EditAnywhere)
		float Damage = 20;

	UPROPERTY(EditAnywhere)
		int MAX_AMMO = 200;

	UPROPERTY(EditAnywhere)
		int MAG_CAPACITY = 20;

	UPROPERTY(VisibleAnywhere)
		int CurrentAmmo;

	UPROPERTY(VisibleAnywhere)
		int AmmoInMag;

	UPROPERTY(EditAnywhere)
		float ReloadTime = 1.6f;

	UPROPERTY(EditAnywhere)		// Shots per second
		float FireRate = 4.f;

	UPROPERTY()
		FTimerHandle ReloadTimeHandler;
};
