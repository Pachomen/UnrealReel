// Fill out your copyright notice in the Description page of Project Settings.


#include "R_ANSMelee.h"
#include "R_Character.h"

void UR_ANSMelee::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor))
	{
		AR_Character* Character = Cast<AR_Character>(CharacterActor);
		if (IsValid(Character))
		{
			Character->SetMeleeDetectorCollision(ECollisionEnabled::QueryOnly);
		}
	}
}

void UR_ANSMelee::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor))
	{
		AR_Character* Character = Cast<AR_Character>(CharacterActor);
		if (IsValid(Character))
		{
			Character->SetMeleeDetectorCollision(ECollisionEnabled::NoCollision);

		}
	}
}
