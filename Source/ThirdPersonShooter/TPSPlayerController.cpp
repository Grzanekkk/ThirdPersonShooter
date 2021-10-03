// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Nameplate.h"

void ATPSPlayerController::BeginPlay()
{
	ControlledPawn = Cast<ATPSCharacter>(GetPawn());
	ControlledPawn->DisplayNameplate(false);

	//Cast<UNameplate>(HUDClass->GetDefaultSubobjectByName("WBP_NamePlate"))->SetOwner(ControlledPawn);
	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
		HUD->AddToViewport();
}

void ATPSPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CanDrawNameplate();
}

void ATPSPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	HUD->RemoveFromViewport();

	if (bIsWinner)	// Win
	{
		UE_LOG(LogTemp, Warning, TEXT("You Win :)"));

		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen != nullptr)
			WinScreen->AddToViewport();
	}
	else			// Loose
	{
		UE_LOG(LogTemp, Warning, TEXT("You Loose :<. Restarting level in %i  seconds"), (int)LevelRestartDelay);

		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen != nullptr)
			LoseScreen->AddToViewport();
	}
	
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, LevelRestartDelay);
	UE_LOG(LogTemp, Warning, TEXT("Wainting..."));
}

void ATPSPlayerController::CanDrawNameplate()
{
	if (ControlledPawn != nullptr)
	{
		FRotator ViewPointRotation;
		FVector ViewPointLocation;
		FHitResult Hit;

		GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
		FVector TraceEnd = ViewPointLocation + ViewPointRotation.Vector() * NamePlateDrawDistance;
		FVector ForwardVector = ControlledPawn->GetCamera()->GetForwardVector();

		bool bSuccess = GetWorld()->SweepSingleByChannel(Hit, ViewPointLocation, TraceEnd, FQuat(ViewPointRotation), ECollisionChannel::ECC_Camera, FCollisionShape::MakeCapsule(10.f, 20.f));
		ATPSCharacter* ActorHit = Cast<ATPSCharacter>(Hit.Actor);

		if (ActorHit != nullptr && ActorHit != ControlledPawn)
		{
			LastSeenActor = ActorHit;
			ActorHit->DisplayNameplate(true);
		}
		else if (LastSeenActor != nullptr)
		{
			LastSeenActor->DisableNameplate();
		}
	}
}