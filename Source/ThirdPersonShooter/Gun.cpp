// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
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

void AGun::PullTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("PEW!"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult HitInfo;
	FVector ShotDirection;
	bool bTargetHit = HitScanTrace(HitInfo, ShotDirection);

	if (bTargetHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletImpact, HitInfo.Location, ShotDirection.Rotation());

		AActor* ActorHit = HitInfo.GetActor();
		if (ActorHit != nullptr)
		{
			AController* OwnerController = GetOwnerController();
			if (OwnerController == nullptr) return;

			FPointDamageEvent DamageEvent(Damage, HitInfo, ShotDirection, nullptr);
			ActorHit->TakeDamage(DamageEvent.Damage, DamageEvent, OwnerController, this);
		}
	}
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

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
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