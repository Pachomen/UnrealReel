// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "R_Door.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class ROOM_API AR_Door : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USceneComponent* CustomeRootComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* DoorframeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* DoorComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
		UBoxComponent* KeyZoneColliderComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My Door")
		float OpenAngle;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Mydoor")
	bool bIsOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My doorr")
	FName DoorTag;
public:	

	// Sets default values for this actor's properties
	AR_Door();




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void checkKeyFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MyDoor")
		void BP_OpenDoor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OpenDoor();


};
