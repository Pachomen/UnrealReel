// Fill out your copyright notice in the Description page of Project Settings.


#include "R_GrenadeLauncher.h"
#include "Weapons/R_Projectile.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
AR_GrenadeLauncher::AR_GrenadeLauncher() 
{

	MuzzleSocketName = "SCK_Muzzle";
}

void AR_GrenadeLauncher::StartAction()
{
	Super::StartAction();

	if (IsValid(CurrentOwnerCharacter))
	{
		USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();
		if (IsValid(CharacterMeshComponent))
		{
			FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
			FRotator MuzzleSocketRotation = CharacterMeshComponent->GetSocketRotation(MuzzleSocketName);
			AR_Projectile* CurrentProjectile = GetWorld()->SpawnActor<AR_Projectile>(ProjectileClass, MuzzleSocketLocation, MuzzleSocketRotation);
		}
	}

}

void AR_GrenadeLauncher::StopAction()
{
	Super::StopAction();
}
