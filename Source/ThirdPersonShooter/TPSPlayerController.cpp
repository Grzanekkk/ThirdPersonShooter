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


