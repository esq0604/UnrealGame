// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_WeaponCollisionToggle.h"

#include "Interface/Combat.h"
#include "Kismet/KismetSystemLibrary.h"

void UAnimNotifyState_WeaponCollisionToggle::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                         float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if(UKismetSystemLibrary::DoesImplementInterface(MeshComp->GetOwner(),UCombat::StaticClass()))
	{
		Cast<ICombat>(MeshComp->GetOwner())->Execute_ToggleWeaponCollision(MeshComp->GetOwner(),true);
	}
}

void UAnimNotifyState_WeaponCollisionToggle::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if(UKismetSystemLibrary::DoesImplementInterface(MeshComp->GetOwner(),UCombat::StaticClass()))
	{
		Cast<ICombat>(MeshComp->GetOwner())->Execute_ToggleWeaponCollision(MeshComp->GetOwner(),false);
	}
}
