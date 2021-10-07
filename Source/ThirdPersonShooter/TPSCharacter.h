// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Blueprint/UserWidget.h"
#include "Gun.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"

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
	//void CanDrawNameplate();
	void DisplayNameplate(bool IsVisible);
	void DisableNameplate();

	UFUNCTION(BlueprintPure)
		bool IsDead() const;

	UFUNCTION(BlueprintPure)
		bool DiedFromBehind() const;

	UFUNCTION(BlueprintPure)
		bool IsShooting() const;

	UFUNCTION(BlueprintPure)
		float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
		float GetHealth() const;

	UFUNCTION(BlueprintPure)
		float GetMaxHealth() const;

	UFUNCTION(BlueprintPure)
		AWeapon* GetEquippedWeapon() const;

	UFUNCTION(BlueprintPure)
		FString GetName() const;

	UFUNCTION(BlueprintPure)
		UCameraComponent* GetCamera() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Reload();
	void Shoot();
	void StopShooting();
	void Die();

	void SpawnWeapon(TSubclassOf<AWeapon> Weapon);

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void LookRight(float AxisValue);
	
	UPROPERTY(EditAnywhere)
		FString Name = TEXT("Default Name");

	UPROPERTY(EditAnywhere)
		float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
		float CurrentHealth = 100;

	UPROPERTY(EditAnywhere)
		bool bIsDead = false;

	UPROPERTY()
		bool bIsShooting = false;

	UPROPERTY(VisibleAnywhere)
		bool bDiedFromBehind = false;

	UPROPERTY(EditAnywhere)
		bool AllowedToShoot = true;

	UPROPERTY(EditAnywhere)
		float ControllerRotarionRate = 50.0f;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AWeapon> EquippedWeaponBP;

	UPROPERTY()
		AWeapon* EquippedGun;

	UPROPERTY(EditAnywhere)
		UWidgetComponent* NameplateWidgetComp;

	UPROPERTY(VisibleAnywhere)
		class UNameplate* Nameplate;
};
