// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/R_Weapon.h"
#include "R_Rifle.generated.h"

class UParticleSystem;

/**
 * 
 */
UCLASS()
class ROOM_API AR_Rifle : public AR_Weapon
{
	GENERATED_BODY()

public:
	AR_Rifle();
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LineTrace|Debug")
		bool bDrawLineTrace;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LineTrace")
		float TraceLenght;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		FName MuzzleSocketName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		FName TraceParamName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		UParticleSystem* MuzzleEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		UParticleSystem* ImpactEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		UParticleSystem* TraceEffect;
protected:

	virtual void StartAction() override;

	virtual void StopAction() override;
};
