// Fill out your copyright notice in the Description page of Project Settings.


#include "R_Platform.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
AR_Platform::AR_Platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomeRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomeRootComponent;

	PlatformMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlatformMeshComponent->SetupAttachment(CustomeRootComponent);

	bIsGoingUp = true;
	Speed = 10.0f;
	MinHeight = 0.0f;
	MaxHeight = 50.0f;
}

// Called when the game starts or when spawned
void AR_Platform::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AR_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void AR_Platform::Move()
{
	FVector upDirection = UKismetMathLibrary :: GetUpVector(GetActorRotation());

	if (bIsGoingUp) {
		
		upDirection = upDirection;
	}
	else {
		upDirection = upDirection * -1;
	}

	FVector CurrentVelocity = upDirection * Speed;
	FVector NewPosition = GetActorLocation() + CurrentVelocity;
	SetActorLocation(NewPosition);

	if ((bIsGoingUp && GetActorLocation().Z >= MaxHeight) || (bIsGoingUp && GetActorLocation().Z <= MinHeight))
	{
		bIsGoingUp = !bIsGoingUp;
	}
}