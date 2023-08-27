// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_ReadAttack.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

void UAnimNotifyState_ReadAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                              float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	// if(AttackBeginTag.IsValid())
	// {
	// 	AttackBeginTag.
	// 	UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(MeshComp->GetOwner())->AddLooseGameplayTag(AttackBeginTag);
	// }
}

void UAnimNotifyState_ReadAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	// if(AttackBeginTag.IsValid())
	// {
	// 	UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(MeshComp->GetOwner())->RemoveLooseGameplayTag(AttackBeginTag);
	// }
}
