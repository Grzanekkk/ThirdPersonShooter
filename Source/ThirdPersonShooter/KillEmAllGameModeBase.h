// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonShooterGameModeBase.h"
#include "KillEmAllGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API AKillEmAllGameModeBase : public AThirdPersonShooterGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
