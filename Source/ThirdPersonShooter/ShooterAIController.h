// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	APawn* AIPawn;
	APawn* PlayerPawn;

	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(EditAnywhere)
		UBehaviorTree* BehaviorTree;
};