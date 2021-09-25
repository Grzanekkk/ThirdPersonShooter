// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"
#include "TimerManager.h"

void ATPSPlayerController::BeginPlay()
{
	UUserWidget* HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
		HUD->AddToViewport();
}

void ATPSPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner)	// Win
	{
		UE_LOG(LogTemp, Warning, TEXT("You Win :)"))
	}
	else			// Loose
	{
		UE_LOG(LogTemp, Warning, TEXT("You Loose :<. Restarting level in %i  seconds"), (int)LevelRestartDelay);

		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen != nullptr)
			LoseScreen->AddToViewport();

		GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, LevelRestartDelay);

	}
}
