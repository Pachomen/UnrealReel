// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "R_GameMode.generated.h"

class AR_Character;
class ARP_SpectatingCamera;

/**
 * 
 */
UCLASS()
class ROOM_API AR_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spectating Camera")
	float SpectatingBlendTime;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
	ARP_SpectatingCamera * VictoryCamera;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
	ARP_SpectatingCamera * GameOverCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupSpectatingCamera();

	void MoveCameraToSpectatingPoint(ARP_SpectatingCamera* SpectatingCamera, AR_Character* Character);

public:

	UFUNCTION()
	void Victory(AR_Character* Character);

	UFUNCTION()
	void GameOver(AR_Character* Character);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Victory(AR_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GameOver(AR_Character* Character);
};
