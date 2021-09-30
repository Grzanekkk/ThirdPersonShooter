// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPSCharacter.h"
#include "Weapon.h"

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API UBTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Shoot();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	ATPSCharacter* AICharacter;
	AWeapon* AIWeapon;
	bool bCanReload = false;
};
