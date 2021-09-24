// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AIPawn = GetOwner();

	if (BehaviorTree != nullptr)
	{
		RunBehaviorTree(BehaviorTree);

		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), Player->GetActorLocation());
	}
	else {
		 UE_LOG(LogTemp, Warning, TEXT("%s has no Behavior Tree attached"), *AIPawn->GetName());
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if (LineOfSightTo(Player))
	// {
	// 	SetFocus(Player);
	// 	MoveToActor(Player, 300.0f);
	// }
	// else
	// {
	// 	ClearFocus(EAIFocusPriority::Gameplay);
	// 	StopMovement();
	// }
}