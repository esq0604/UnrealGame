// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CustomAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UCustomAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	UCustomAbilitySystemComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Abilities")
FGameplayAbilitySpecHandle FindAbilitySpecHandleForClass(TSubclassOf<UGameplayAbility> AbilityClass, UObject* OptionalSourceObject=nullptr);

};
