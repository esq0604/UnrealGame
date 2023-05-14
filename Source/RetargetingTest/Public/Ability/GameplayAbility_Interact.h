// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Interact.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UGameplayAbility_Interact : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGameplayAbility_Interact(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	//UFUNCTION(BlueprintCallable)
	
};
