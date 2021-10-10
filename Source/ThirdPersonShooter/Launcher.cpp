// Fill out your copyright notice in the Description page of Project Settings.


#include "Launcher.h"


ALauncher::ALauncher()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void ALauncher::BeginPlay()
{
	AWeapon::BeginPlay();

}

bool ALauncher::PullTrigger()
{
	AWeapon::PullTrigger();

	return false;
}

void ALauncher::Reload()
{
	AWeapon::Reload();
}
