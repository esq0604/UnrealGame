// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_BranchAttack.h"

#include "AbilitySystemComponent.h"



void UAnimNotifyState_BranchAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	FGameplayEventData PayLoad;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(),FGameplayTag::RequestGameplayTag("Ability.State.NextAttack"),PayLoad);
}

