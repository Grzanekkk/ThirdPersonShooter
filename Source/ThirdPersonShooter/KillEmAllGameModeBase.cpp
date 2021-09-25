// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameModeBase.h"

void AKillEmAllGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	UE_LOG(LogTemp, Warning, TEXT("Pawn died!"));
}
