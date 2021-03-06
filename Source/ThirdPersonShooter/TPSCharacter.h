// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Gun.h"
#include "InventoryComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "TimerManager.h"

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

	UFUNCTION(BlueprintPure, Category = "Health")
		FORCEINLINE bool IsDead() const { return bIsDead; }

	UFUNCTION(BlueprintPure, Category = "Health")
		FORCEINLINE bool DiedFromBehind() const { return bDiedFromBehind; }

	UFUNCTION(BlueprintPure, Category = "Health")
		FORCEINLINE bool IsShooting() const { return bIsShooting; }

	UFUNCTION(BlueprintPure, Category = "Health")
		FORCEINLINE float GetHealthPercent() const { return CurrentHealth / MaxHealth; }

	UFUNCTION(BlueprintPure, Category = "Health")
		FORCEINLINE float GetHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintPure, Category = "Health")
		FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintPure, Category = "Weapons")
		AWeapon* GetEquippedWeapon() const { return EquippedGun; }

	UFUNCTION(BlueprintPure, Category = "Name")
		FString GetName() const { return Name; }

	UFUNCTION(BlueprintPure, Category = "Camera")
		UCameraComponent* GetCamera() const { return FindComponentByClass<UCameraComponent>(); }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Reload();
	void Shoot();
	void StopShooting();
	void Die();
	void SetWeapon(TSubclassOf<AWeapon> Weapon);

	void SwapWeapons();

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
		float ControllerRotarionRate = 50.0f;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AWeapon> EquippedWeaponBP;

	UPROPERTY()
		AWeapon* EquippedGun;

	UPROPERTY()
		UInventoryComponent* InventoryComp;

	UPROPERTY(EditAnywhere)
		UWidgetComponent* NameplateWidgetComp;

	UPROPERTY(VisibleAnywhere)
		class UNameplate* Nameplate;

	UPROPERTY()
		FTimerHandle TimeHandler;
};
