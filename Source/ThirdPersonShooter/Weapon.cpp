// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"

#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AController* AWeapon::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());                                   
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}

bool AWeapon::PullTrigger()
{
	if (AmmoInMag == 0)
	{
		UGameplayStatics::SpawnSoundAttached(EmptyMagSound, Mesh, TEXT("MuzzleFlashSocket"));
		return false;
	}

	AmmoInMag--;

	UE_LOG(LogTemp, Warning, TEXT("PEW!"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	return true;
}

void AWeapon::Reload()
{
	if (AmmoInMag != MAG_CAPACITY)
	{
		GetWorldTimerManager().SetTimer(ReloadTimeHandler, this, &AWeapon::ReloadAfterDelay, ReloadTime);
		UGameplayStatics::SpawnSoundAttached(ReloadSound, Mesh, TEXT("MuzzleFlashSocket"));
	}
}

void AWeapon::ReloadAfterDelay()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading!"));

	int AmmoToReload = FMath::Min(MAG_CAPACITY - AmmoInMag, CurrentAmmo);	// Prevents from reloading more ammo then we have
	AmmoInMag += AmmoToReload;
	CurrentAmmo -= AmmoToReload;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

