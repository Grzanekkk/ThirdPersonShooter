// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LocatePlayer.h"
#include "AIController.h"

UBTService_LocatePlayer::UBTService_LocatePlayer()
{
	NodeName = "Update Player Location If Seen";
}

void UBTService_LocatePlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
		BlackboardComponent->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
	else
		BlackboardComponent->ClearValue(GetSelectedBlackboardKey());
}


