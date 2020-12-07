// Fill out your copyright notice in the Description page of Project Settings.


#include "R_DoorKey.h"
#include "Components/StaticMeshComponent.h"
#include "R_Character.h"
AR_DoorKey::AR_DoorKey()
{
	KeyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshComponent"));
	KeyMeshComponent->SetupAttachment(RootComponent);
	KeyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	KeyTag = "Key_A";
}

void AR_DoorKey::Pickup(AR_Character* PickupActor)
{
	Super::Pickup(PickupActor);

	PickupActor->AddKey(KeyTag);
	Destroy();
}
