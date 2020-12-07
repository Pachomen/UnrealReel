// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/R_Weapon.h"
#include "R_GrenadeLauncher.generated.h"

class AR_Projectile;

/**
 * 
 */
UCLASS()
class ROOM_API AR_GrenadeLauncher : public AR_Weapon
{
	GENERATED_BODY()

public:

	AR_GrenadeLauncher();

protected:

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		FName MuzzleSocketName;
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grenade Launcher")
		TSubclassOf<AR_Projectile> ProjectileClass;
	
protected:

		virtual void StartAction() override;


		virtual void StopAction() override;
};
