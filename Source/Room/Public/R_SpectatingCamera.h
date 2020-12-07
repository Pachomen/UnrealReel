// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "R_SpectatingCamera.generated.h"

class UStaticMeshComponent;

UENUM()
enum class ER_SpectatingCameraType : uint8
{
	CameraType_None		UMETA(DisplayName = "None"),
	CameraType_Victory  UMETA(DisplayName = "Victory"),
	CameraType_GameOve  UMETA(DisplayName = "GameOver")
};


UCLASS()
class ROOM_API AR_SpectatingCamera : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SpectatingCameraComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spectating Camera")
	ER_SpectatingCameraType CameraType;
public:	
	// Sets default values for this actor's properties
	AR_SpectatingCamera();

	ER_SpectatingCameraType GetCameraType() { return CameraType; };


};
