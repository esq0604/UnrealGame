// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_BranchAttack.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UAnimNotifyState_BranchAttack : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
public:
	
};

 
