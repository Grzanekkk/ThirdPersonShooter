// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API ATPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
		float LevelRestartDelay = 5.f;

	FTimerHandle RestartTimer;
};
