// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "BaseAbilityObject.generated.h"

/**
 * 
 */
class UAnimMontage;

UCLASS()
class RETARGETINGTEST_API UBaseAbilityObject : public UObject
{
	GENERATED_BODY()
public:
	UBaseAbilityObject();

	/* Ability Setters */
	UFUNCTION(BlueprintCallable, Category = "Ability Setters")
	void SetActiveAbilityMontage(UAnimMontage* NewActiveMontage);
	
	UFUNCTION(BlueprintCallable, Category = "Ability Setters")
	void SetPerformingActor(AActor* NewPerformingActor);
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Properties")
	FGameplayTag AbilityGameplayTag;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Ability Properties")
	UAnimMontage* ActiveAbilityMontage;

	UPROPERTY()
	AActor* PerformingActor;
};
