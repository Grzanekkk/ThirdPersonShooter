// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AICharacter = Cast<ATPSCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AIWeapon = AICharacter->GetWieldedWeapon();

	if (AICharacter == nullptr)
		return EBTNodeResult::Failed;

	if (AIWeapon->GetLoadedAmmo() != 0)
	{
		bCanReload = true;
		AICharacter->ATPSCharacter::Shoot();
	}
	else if(bCanReload)
	{
		bCanReload = false;
		AICharacter->Reload();
	}

	return EBTNodeResult::Succeeded;
}