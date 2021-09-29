// Fill out your copyright notice in the Description page of Project Settings.

#include "TPSCharacter.h"
#include "ThirdPersonShooterGameModeBase.h"

#include "Components/CapsuleComponent.h"

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
}

// Called every frame
void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATPSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!IsDead())
	{
		FPointDamageEvent Event = *((FPointDamageEvent*)&DamageEvent);
		FVector ShotDirection = Event.ShotDirection;

		float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		DamageToApply = FMath::Min(CurrentHealth, DamageToApply);	// Prevents HP to go below 0
		CurrentHealth -= DamageToApply;

		UE_LOG(LogTemp, Warning, TEXT("Actor hit! Current health: %f. Shot direction: %s"), CurrentHealth, *ShotDirection.ToString());

		if (CurrentHealth <= 0)
		{
			if (ShotDirection.Y > 0)
				bDiedFromBehind = true;

			Die();
		}

		return DamageToApply;
	}

	return 0;
}

void ATPSCharacter::Die()
{
	bIsDead = true;

	AThirdPersonShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AThirdPersonShooterGameModeBase>();
	if (GameMode != nullptr)
		GameMode->PawnKilled(this);
	
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

bool ATPSCharacter::IsDead() const
{
	return bIsDead;
}

float ATPSCharacter::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

bool ATPSCharacter::DiedFromBehind() const
{
	return bDiedFromBehind;
}

bool ATPSCharacter::IsShooting() const
{
	return bIsShooting;
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
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Released, this, &ATPSCharacter::StopShooting);
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
	bIsShooting = true;
	Gun->PullTrigger();
}

void ATPSCharacter::StopShooting()
{
	bIsShooting = false;
}


