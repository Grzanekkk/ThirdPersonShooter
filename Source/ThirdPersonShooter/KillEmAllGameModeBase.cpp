// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameModeBase.h"
#include "TPSPlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	UE_LOG(LogTemp, Warning, TEXT("Pawn died!"));

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)	// Checks if Pawn killed was a Player
	{
		EndGame(false);
	}

	for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!AIController->IsDead())
			return;	
	}

	EndGame(true);
}


void AKillEmAllGameModeBase::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld())) 
	{
		bool bIsControllerWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsControllerWinner);
	}
}