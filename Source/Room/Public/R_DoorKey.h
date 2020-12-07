// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/R_Item.h"
#include "R_DoorKey.generated.h"

class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class ROOM_API AR_DoorKey : public AR_Item
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* KeyMeshComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key")
	FName KeyTag;

public:

	AR_DoorKey();

public:

	UFUNCTION( BlueprintCallable, Category = "Getter")
	FName GetKeyTag() const { return KeyTag; };

protected:
	virtual void Pickup(AR_Character* PickupActor) override;

};
