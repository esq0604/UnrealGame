// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RetargetingTest/RetargetingTest.h"
#include "CharacterGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UCharacterGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UCharacterGameplayAbility();

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Ability")
	AbilityID AbilityInputID = AbilityID::None;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Ability")
	AbilityID AbilityID = AbilityID::None;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Ability")
	bool ActivateAbilityOnGranted =false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
};