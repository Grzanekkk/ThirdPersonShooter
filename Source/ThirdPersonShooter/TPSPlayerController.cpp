// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"
#include "TimerManager.h"
#include "Engine/World.h"

void ATPSPlayerController::BeginPlay()
{
	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
		HUD->AddToViewport();

	ControlledPawn = Cast<ATPSCharacter>(GetPawn());
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
	FRotator ViewPointRotation;
	FVector ViewPointLocation;
	FHitResult Hit;

	GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
	FVector TraceEnd = ViewPointLocation + ViewPointRotation.Vector() * NamePlateDrawDistance;
	FVector ForwardVector = ControlledPawn->GetCamera()->GetForwardVector();

	bool bSuccess = GetWorld()->SweepSingleByChannel(Hit, ViewPointLocation, TraceEnd, FQuat(ViewPointRotation), ECollisionChannel::ECC_Camera, FCollisionShape::MakeCapsule(34.f, 88.f));
	ATPSCharacter* ActorHit = Cast<ATPSCharacter>(Hit.Actor);

	if (ActorHit != nullptr)
		ActorHit->DisplayNameplate(bSuccess);
}


