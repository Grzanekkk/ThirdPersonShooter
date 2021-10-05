// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"

#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

}

bool AWeapon::PullTrigger()
{
	if (LoadedAmmo == 0)
	{
		UGameplayStatics::SpawnSoundAttached(EmptyMagSound, Mesh, TEXT("MuzzleFlashSocket"));
		return false;
	}

	LoadedAmmo--;

	UE_LOG(LogTemp, Warning, TEXT("PEW!"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	return true;
}

void AWeapon::Reload()
{
	if (LoadedAmmo != MAG_CAPACITY)
	{
		GetWorldTimerManager().SetTimer(ReloadTimeHandler, this, &AWeapon::ReloadAfterDelay, ReloadTime);
		UGameplayStatics::SpawnSoundAttached(ReloadSound, Mesh, TEXT("MuzzleFlashSocket"));
	}
}

void AWeapon::ReloadAfterDelay()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading!"));

	int AmmoToReload = FMath::Min(MAG_CAPACITY - LoadedAmmo, CurrentAmmo);	// Prevents from reloading more ammo then we have
	LoadedAmmo += AmmoToReload;
	CurrentAmmo -= AmmoToReload;
}

AController* AWeapon::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}

int AWeapon::GetLoadedAmmo() const
{
	return LoadedAmmo;
}

FString AWeapon::GetName() const
{
	return Name;
}

int AWeapon::GetCurrentAmmo() const
{
	return CurrentAmmo;
}

UTexture2D* AWeapon::GetIcon() const
{
	return WeaponIcon;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MAX_AMMO;
	LoadedAmmo = MAG_CAPACITY;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}