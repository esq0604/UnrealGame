// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility_MeleeWeapon.h"
#include "UObject/Object.h"
#include "GameplayAbility_TwinbladeComboBase.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UGameplayAbility_TwinbladeComboBase : public UGameplayAbility_MeleeWeapon
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UFUNCTION()
	void NextAttackEventReceived(FGameplayEventData Payload);
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	bool IsFirstAttack;
	
};
