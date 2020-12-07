// Fill out your copyright notice in the Description page of Project Settings.


#include "R_ANEnableAction.h"
#include "R_Character.h"


void UR_ANEnableAction::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor))
	{
		AR_Character* Character = Cast<AR_Character>(CharacterActor);
		if (IsValid(Character))
		{
			Character->SetMeleeState(false);

		}
	}
}
