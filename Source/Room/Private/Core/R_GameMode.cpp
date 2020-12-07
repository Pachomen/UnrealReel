// Fill out your copyright notice in the Description page of Project Settings.


#include "R_GameMode.h"
#include "R_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RP_SpectatingCamera.h"

void AR_GameMode::BeginPlay()
{
	Super::BeginPlay();
	SetupSpectatingCamera();
}

void AR_GameMode::SetupSpectatingCamera()
{
	TArray<AActor*> SpectatingCameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARP_SpectatingCamera::StaticClass(), SpectatingCameraActors);

	if (SpectatingCameraActors.Num() > 0)
	{
		for (AActor* SpectatingActor : SpectatingCameraActors)
		{
			ARP_SpectatingCamera* SpectatingCamera = Cast<ARP_SpectatingCamera>(SpectatingActor);
			if (IsValid(SpectatingCamera))
			{
				switch (SpectatingCamera->GetCameraType())
				{
				case ERP_SpectatingCameraType::CameraType_Victory:
					VictoryCamera = SpectatingCamera;
					break;
				case ERP_SpectatingCameraType::CameraType_GameOve:
						GameOverCamera = SpectatingCamera;
						break;
					default:
						break;
				}
			}
		}
	}
}

void AR_GameMode::MoveCameraToSpectatingPoint(ARP_SpectatingCamera* SpectatingCamera, AR_Character* Character)
{
	if (!IsValid(Character) || !IsValid(SpectatingCamera))
	{
		return;
	}
	if (IsValid(Character) && IsValid(SpectatingCamera))
	{
		AController* CharacterController = Character->GetController();
		if (IsValid(CharacterController))
		{
			APlayerController* PlayerController = Cast<APlayerController>(CharacterController);
			if (IsValid(PlayerController))
			{
				PlayerController->SetViewTargetWithBlend(SpectatingCamera, SpectatingBlendTime, EViewTargetBlendFunction::VTBlend_Cubic);
			}
		}
	}
}

void AR_GameMode::Victory(AR_Character* Character)
{
	Character->DisableInput(nullptr);
	MoveCameraToSpectatingPoint(VictoryCamera, Character);
	BP_Victory(Character);

}


void AR_GameMode::GameOver(AR_Character* Character)
{
	Character->GetMovementComponent()->StopMovementImmediately();
	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (Character->HasToDestroy())
	{
		Character->DetachFromControllerPendingDestroy();
		Character->SetLifeSpan(5.0f);
	}
	else 
	{
		Character->DisableInput(nullptr);
		MoveCameraToSpectatingPoint(GameOverCamera, Character);
	}

	BP_GameOver(Character);
}
