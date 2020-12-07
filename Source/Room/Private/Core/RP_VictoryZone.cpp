// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RP_VictoryZone.h"
#include "Components/BoxComponent.h"
#include "R_Character.h"
#include "Core/R_GameMode.h"

// Sets default values
ARP_VictoryZone::ARP_VictoryZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VictoryZoneComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("VictoryZoneComponent"));
	RootComponent = VictoryZoneComponent;
	VictoryZoneComponent->SetBoxExtent(FVector(100.0f));
}

// Called when the game starts or when spawned
void ARP_VictoryZone::BeginPlay()
{
	Super::BeginPlay();
	
	GameModeReference = Cast<AR_GameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void ARP_VictoryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARP_VictoryZone::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (IsValid(OtherActor) && IsValid(GameModeReference))
	{
		AR_Character* RPCharacter = Cast<AR_Character>(OtherActor);
		if (IsValid(RPCharacter))
		{
			GameModeReference->Victory(RPCharacter);
		}
	}
}

