// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

TSubclassOf<AWeapon> UInventoryComponent::SwapWeapon()
{
	if (SelectedWeaponSlot == 0)
		SelectedWeaponSlot = 1;
	else
		SelectedWeaponSlot = 0;

	return Weapons[SelectedWeaponSlot];
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Weapons.Add(WeaponSlot1);
	Weapons.Add(WeaponSlot2);
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

