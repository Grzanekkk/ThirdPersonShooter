// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCharacter.h"

// Sets default values
ATPSCharacter::ATPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunSubclass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
	

	// UUserWidget* HUD = CreateWidget(GetWorld(), HUDClass);		// SUPER TEMPORARY
	// if (HUD != nullptr)
	// {
	// 	HUD->AddToViewport();
	// }
}

// Called every frame
void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATPSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(CurrentHealth, DamageToApply);	// Prevents HP to go below 0
	CurrentHealth -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Actor hit! Current health: %f"), CurrentHealth);

	if (CurrentHealth <= 0)
	{
		Die();
	}

	return DamageToApply;
}

void ATPSCharacter::Die()
{
	IsActorDead = true;
}

bool ATPSCharacter::IsDead() const
{
	return IsActorDead;
}

// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATPSCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ATPSCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ATPSCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &ATPSCharacter::LookRightRate);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &ATPSCharacter::LookRight);
	
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &ATPSCharacter::Shoot);
}

void ATPSCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ATPSCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ATPSCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ATPSCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ATPSCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * ControllerRotarionRate * GetWorld()->DeltaTimeSeconds);
}

void ATPSCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * ControllerRotarionRate * GetWorld()->DeltaTimeSeconds);
}

void ATPSCharacter::Shoot()
{
	Gun->PullTrigger();
}


