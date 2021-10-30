// Fill out your copyright notice in the Description page of Project Settings.

#include "TPSCharacter.h"
#include "ThirdPersonShooterGameModeBase.h"

#include "Nameplate.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ATPSCharacter::ATPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NameplateWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameplateWidget"));
	NameplateWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}


// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	InventoryComp = FindComponentByClass<UInventoryComponent>();

	CurrentHealth = MaxHealth;

	//SetWeapon(EquippedWeaponBP);
	SwapWeapons();
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	if (!GetController()->IsPlayerController())
	{
		Nameplate = Cast<UNameplate>(NameplateWidgetComp->GetUserWidgetObject());
		Nameplate->SetOwner(this);
	}

	DisableNameplate();
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
			if (ShotDirection.Y > 0)		// Kinda not working
				bDiedFromBehind = true;

			Die();
		}

		return DamageToApply;
	}

	return 0;
}

void ATPSCharacter::DisplayNameplate(bool IsVisible)
{
	if(!IsDead())
		NameplateWidgetComp->SetVisibility(IsVisible);
}

void ATPSCharacter::DisableNameplate()
{
	NameplateWidgetComp->SetVisibility(false);
}

void ATPSCharacter::Die()
{
	DisableNameplate();

	bIsDead = true;

	AThirdPersonShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AThirdPersonShooterGameModeBase>();
	if (GameMode != nullptr)
		GameMode->PawnKilled(this);
	
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATPSCharacter::SwapWeapons()
{
	if(InventoryComp != nullptr)
		SetWeapon(InventoryComp->SwapWeapon());
}

void ATPSCharacter::SetWeapon(TSubclassOf<AWeapon> Weapon)
{
	if (EquippedGun != nullptr)
		EquippedGun->Destroy();

	EquippedGun = GetWorld()->SpawnActor<AWeapon>(Weapon);
	if (EquippedGun == nullptr)
		return;
	EquippedGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	EquippedGun->SetOwner(this);
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
	
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &ATPSCharacter::Reload);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &ATPSCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Released, this, &ATPSCharacter::StopShooting);
	PlayerInputComponent->BindAction(TEXT("SwapWeapon"), EInputEvent::IE_Released, this, &ATPSCharacter::SwapWeapons);
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
	if (AllowedToShoot)
	{
		if (EquippedGun->PullTrigger())
			bIsShooting = true;
	}
}

void ATPSCharacter::StopShooting()
{
	bIsShooting = false;
}

void ATPSCharacter::Reload()
{
	EquippedGun->Reload();
}