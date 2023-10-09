// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RetargetingTest/RetargetingTest.h"
#include "CustomGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UCustomGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Ability")
	EAbilityInputID AbilityInputID{EAbilityInputID::None};
	
};
