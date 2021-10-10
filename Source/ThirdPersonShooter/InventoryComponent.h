// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONSHOOTER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	TSubclassOf<AWeapon> SwapWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	unsigned int SelectedWeaponSlot = 0;
	TArray<TSubclassOf<AWeapon>> Weapons;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponSlot1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponSlot2;
};
