// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

bool AGun::PullTrigger()
{
	if (!AWeapon::PullTrigger())
		return false;

	FHitResult HitInfo;
	FVector ShotDirection;
	bool bTargetHit = HitScanTrace(HitInfo, ShotDirection);

	if (bTargetHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletImpact, HitInfo.Location, ShotDirection.Rotation());

		APawn* PawnHit = Cast<APawn>(HitInfo.GetActor());
		if (PawnHit != nullptr)
		{
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), EnemyImpactSound, HitInfo.Location, ShotDirection.Rotation());
			UE_LOG(LogTemp, Warning, TEXT("Actor Hit!"));
			AController* OwnerController = GetOwnerController();
			if (OwnerController == nullptr) return true;

			FPointDamageEvent DamageEvent(Damage, HitInfo, ShotDirection, nullptr);
			PawnHit->TakeDamage(DamageEvent.Damage, DamageEvent, OwnerController, this);
		}
		else	// We didn't hit an actor
		{
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), TerrainImpactSound, HitInfo.Location, ShotDirection.Rotation());
		}
	}

	return true;
}

void AGun::Reload()
{
	AWeapon::Reload();
}

bool AGun::HitScanTrace(FHitResult& outHitInfo, FVector& outShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return false;

	FRotator ViewPointRotation;
	FVector ViewPointLocation;

	OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
	outShotDirection = -ViewPointRotation.Vector();

	FVector LineTraceEnd = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	//DrawDebugLine(GetWorld(), ViewPointLocation, LineTraceEnd, FColor::Blue, true, 10.0f, 10, 5.0f);

	return GetWorld()->LineTraceSingleByChannel(outHitInfo, ViewPointLocation, LineTraceEnd, ECollisionChannel::ECC_GameTraceChannel1, Params);	// ECC_EngineTraceChannel1 == "Bullet" trace channel
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}