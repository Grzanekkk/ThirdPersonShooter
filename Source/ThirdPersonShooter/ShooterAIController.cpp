// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AIPawn = GetPawn();

	if (BehaviorTree != nullptr)
	{
		RunBehaviorTree(BehaviorTree);
		BlackboardComponent = GetBlackboardComponent();

		BlackboardComponent->SetValueAsVector(TEXT("StartLocation"), AIPawn->GetActorLocation());

		BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	}
	else {
		 UE_LOG(LogTemp, Warning, TEXT("%s has no Behavior Tree attached"), *AIPawn->GetName());
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LineOfSightTo(PlayerPawn))
	{
		SetFocus(PlayerPawn);
		BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		BlackboardComponent->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		BlackboardComponent->ClearValue(TEXT("PlayerLocation"));
	}






	// if (LineOfSightTo(PlayerPawn))
	// {
	// 	SetFocus(PlayerPawn);
	// 	MoveToActor(Player, 300.0f);
	// }
	// else
	// {
	// 	ClearFocus(EAIFocusPriority::Gameplay);
	// 	StopMovement();
	// }
}