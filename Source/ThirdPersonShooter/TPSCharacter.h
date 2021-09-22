// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Blueprint/UserWidget.h"
#include "Gun.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSCharacter.generated.h"


UCLASS()
class THIRDPERSONSHOOTER_API ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintPure)
		bool IsDead() const;

	UFUNCTION(BlueprintPure)
		bool DiedFromBehind() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void LookRight(float AxisValue);
	void Shoot();
	void Die();

	UPROPERTY(EditAnywhere)
		float MaxHealth = 100;

	UPROPERTY(EditDefaultsOnly)
		float CurrentHealth;

	UPROPERTY(EditAnywhere)
		bool bIsDead = false;

	UPROPERTY(VisibleAnywhere)
		bool bDiedFromBehind = false;

	UPROPERTY(EditAnywhere)
		float ControllerRotarionRate = 50.0f;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGun> GunSubclass;

	UPROPERTY()
		AGun* Gun;

	// UPROPERTY(EditAnywhere)
	// 	TSubclassOf<class UUserWidget> HUDClass;

};
