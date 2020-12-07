// Fill out your copyright notice in the Description page of Project Settings.


#include "R_Character.h"
#include "Room.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Weapons/R_Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/R_HealthComponent.h"
#include "Core/R_GameMode.h"
// Sets default values
AR_Character::AR_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseFirstPersonView = true;
	FPSCameraSocketName = "SCK_Camera";
	MeleeSocketName = "SCK_Melee";
	MeeleDamage = 10.0f;
	MaxComboMultiplier = 4.0f;
	CurrentComboMutiplier = 1.0f;
	

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_CameraComponent"));
	FPSCameraComponent->bUsePawnControlRotation = true;
	FPSCameraComponent->SetupAttachment(GetMesh(), FPSCameraSocketName);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS_CameraComponent"));
	TPSCameraComponent->SetupAttachment(SpringArmComponent);

	MeleeDetectorComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeDetectorComponent"));
	MeleeDetectorComponent->SetupAttachment(GetMesh(), MeleeSocketName);
	MeleeDetectorComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeDetectorComponent->SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Overlap);
	MeleeDetectorComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealthComponent = CreateDefaultSubobject<UR_HealthComponent>(TEXT("HealthComponent"));
	
	
}

FVector AR_Character::GetPawnViewLocation() const
{
	if (IsValid(FPSCameraComponent) && bUseFirstPersonView) 
	{
	
		return FPSCameraComponent->GetComponentLocation();
	}
	if (IsValid(TPSCameraComponent) && !bUseFirstPersonView)
	{
		return TPSCameraComponent->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}

// Called when the game starts or when spawned
void AR_Character::BeginPlay()
{
	Super::BeginPlay();
	InitializeReferences();
	CreateInitialWeapon();
	MeleeDetectorComponent->OnComponentBeginOverlap.AddDynamic(this, &AR_Character::MakeMeleeDamage);

	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AR_Character::OnHealthChange);
}

void AR_Character::InitializeReferences()
{
	if (IsValid(GetMesh()))
	{
		MyAnimInstance = GetMesh()->GetAnimInstance();
	}

	GameModeReference = Cast<AR_GameMode>(GetWorld()->GetAuthGameMode());
}

void AR_Character::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector() * value);
}

void AR_Character::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * value);
}

void AR_Character::Jump()
{
	Super::Jump();
}

void AR_Character::StopJumping()
{
	Super::StopJumping();
}

void AR_Character::CreateInitialWeapon()
{
	if (IsValid(InitialWeaponClass))
	{

		CurrentWeapon = GetWorld()->SpawnActor<AR_Weapon>(InitialWeaponClass, GetActorLocation(), GetActorRotation());
		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetCharacterOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

void AR_Character::StartWeaponAction()
{
	if (!bCansUseWeapon)
	{
		return;
	}
	if (IsValid(CurrentWeapon)) 
	{
		CurrentWeapon->StartAction();

	}

}

void AR_Character::StopWeaponAction()
{
	if (!bCansUseWeapon)
	{
		return;
	}
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StopAction();

	}

}

void AR_Character::StartMelee()
{
	if (bIsDoingMelee && !bCanMakeCombos)
	{
		return;
	}

	if (bCanMakeCombos)
	{
		if (bIsDoingMelee) 
		{
			if (bIsComboEnable) 
			{
				if (CurrentComboMutiplier < MaxComboMultiplier)
				{
					CurrentComboMutiplier++;
					SetComboEnable(false);
				}
				else 
				{
					return;
				}
			}
			else 
			{
				return;
			}
		}

	}



	if (IsValid(MyAnimInstance) && IsValid(MeleeMontage))
	{
		MyAnimInstance->Montage_Play(MeleeMontage);
	}

	SetMeleeState(true);
}

void AR_Character::StopMelee()
{
	UE_LOG(LogTemp, Warning, TEXT("Player stop melee action"))

}

void AR_Character::MakeMeleeDamage(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(OtherActor))
	{
		UGameplayStatics::ApplyPointDamage(OtherActor, MeeleDamage * CurrentComboMutiplier, SweepResult.Location, SweepResult, GetInstigatorController(), this, nullptr);
	}
}

void AR_Character::OnHealthChange(UR_HealthComponent * CurrrentHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (HealthComponent->IsDead())
	{
		if (IsValid(GameModeReference))
		{
			GameModeReference->GameOver(this);
		}
	}
}

void AR_Character::AddControllerPitchInput(float value)
{

	Super::AddControllerPitchInput(bIsLooInverrsion? -value : value);
}



// Called every frame
void AR_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AR_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AR_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AR_Character::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AR_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &ACharacter::AddControllerYawInput);


	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AR_Character::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AR_Character::StopJumping);

	PlayerInputComponent->BindAction("WeaponAction", IE_Pressed, this, &AR_Character::StartWeaponAction);
	PlayerInputComponent->BindAction("WeaponAction", IE_Released, this, &AR_Character::StopWeaponAction);


	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &AR_Character::StartMelee);
	PlayerInputComponent->BindAction("Melee", IE_Released, this, &AR_Character::StopMelee);
}

void AR_Character::AddKey(FName NewKey)
{
	DoorKeys.Add(NewKey);
}

bool AR_Character::HasKey(FName KeyTag)
{
	return DoorKeys.Contains(KeyTag);
}

void AR_Character::SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState)
{
	MeleeDetectorComponent->SetCollisionEnabled(NewCollisionState);
}

void AR_Character::SetMeleeState(bool NewState)
{

	bIsDoingMelee = NewState;
	bCansUseWeapon = !NewState;
}

void AR_Character::SetComboEnable(bool NewState)
{
	bIsComboEnable = NewState;
}

void AR_Character::ResetCombo()
{
	SetComboEnable(false);
	CurrentComboMutiplier = 1.0f;
}

