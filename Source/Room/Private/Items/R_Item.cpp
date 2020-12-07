// Fill out your copyright notice in the Description page of Project Settings.


#include "R_Item.h"
#include "Components/SphereComponent.h"
#include "R_Character.h"

// Sets default values
AR_Item::AR_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MainColliderComponent"));
	MainColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = MainColliderComponent;



}

// Called when the game starts or when spawned
void AR_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AR_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AR_Item::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor))
	{
	
		AR_Character* OverlappedCharacter = Cast<AR_Character>(OtherActor);
		if (IsValid(OverlappedCharacter))
		{
			Pickup(OverlappedCharacter);
		}

	}
}

void AR_Item::Pickup(AR_Character* PickupActor)
{
	BP_Pickup(PickupActor);
}