// Fill out your copyright notice in the Description page of Project Settings.


#include "R_Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components//BoxComponent.h"
#include "R_Character.h"
// Sets default values
AR_Door::AR_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomeRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomeRootComponent;

	DoorframeComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorframeComponent->SetupAttachment(CustomeRootComponent);

	DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorComponent->SetupAttachment(CustomeRootComponent);

	KeyZoneColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyZoneCollider"));
	KeyZoneColliderComponent->SetupAttachment(CustomeRootComponent);
	KeyZoneColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	KeyZoneColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	KeyZoneColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	OpenAngle = 90.0f;

	DoorTag = "Key_A";
}

// Called when the game starts or when spawned
void AR_Door::BeginPlay()
{
	Super::BeginPlay();

	KeyZoneColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AR_Door::checkKeyFromPlayer);
}

void AR_Door::checkKeyFromPlayer(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bIsOpen)
	{
		return;
	}
	if (IsValid(OtherActor)) 
	{
	
		AR_Character* OverlappedCharacter = Cast<AR_Character>(OtherActor);
		if (IsValid(OverlappedCharacter))
		{
			if (OverlappedCharacter->HasKey(DoorTag))
			{
				OpenDoor();
			}

		}
	}
}

// Called every frame
void AR_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AR_Door::OpenDoor()
{
// 	FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);
// 	DoorComponent->SetRelativeRotation(NewRotation);
	bIsOpen = true;

	BP_OpenDoor();
}

