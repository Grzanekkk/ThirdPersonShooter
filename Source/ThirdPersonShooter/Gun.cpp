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

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;

	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FRotator ViewPointRotation;
	FVector ViewPointLocation;

	OwnerController->GetActorEyesViewPoint(ViewPointLocation, ViewPointRotation);
	
	FVector LineTraceEnd = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;
	//FVector LineTraceEnd = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;

	//DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotation, 90, 1, FColor::Red, true);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	FHitResult HitInfo;
	bool bTargetHit = GetWorld()->LineTraceSingleByChannel(HitInfo, ViewPointLocation, LineTraceEnd, ECollisionChannel::ECC_GameTraceChannel1, Params);	// ECC_EngineTraceChannel1 == "Bullet" trace channel

	if (bTargetHit)
	{
		//DrawDebugPoint(GetWorld(), TargetHit.Location, 15, FColor::Red, true);
		FVector ShotDirection = -ViewPointRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletImpact, HitInfo.Location, ShotDirection.Rotation());

		AActor* ActorHit = HitInfo.GetActor();
		if (ActorHit != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, HitInfo, ShotDirection, nullptr);
			ActorHit->TakeDamage(DamageEvent.Damage, DamageEvent, OwnerController, this);
		}
	}
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

