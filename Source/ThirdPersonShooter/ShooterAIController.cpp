// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "TPSCharacter.h"

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
}

bool AShooterAIController::IsDead() const
{
	ATPSCharacter* ControllerCharacter = Cast<ATPSCharacter>(GetPawn());
	if (ControllerCharacter != nullptr)
		return ControllerCharacter->IsDead();

	return true;	// If we don't control anything, just say it's dead.
}