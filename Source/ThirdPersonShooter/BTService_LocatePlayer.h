// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_LocatePlayer.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API UBTService_LocatePlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_LocatePlayer();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	APawn* PlayerPawn;
	UBlackboardComponent* BlackboardComponent;
};
