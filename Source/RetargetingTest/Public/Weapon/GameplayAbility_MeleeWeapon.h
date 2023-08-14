// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_MeleeWeapon.generated.h"

class ABaseWeaponInstance;
/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UGameplayAbility_MeleeWeapon : public UGameplayAbility
{
	GENERATED_BODY()
public:
	explicit UGameplayAbility_MeleeWeapon(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category="Game|Ability")
	ABaseWeaponInstance* GetWeaponInstance();
	
	//~UGameplayAbility interface

protected:
	void PerformTrace(OUT TArray<FHitResult>& OutHits);
	UFUNCTION(BlueprintCallable)
	void StartWeaponTraceForTarget();
	
};
