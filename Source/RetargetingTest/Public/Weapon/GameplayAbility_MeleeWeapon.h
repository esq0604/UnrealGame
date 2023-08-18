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

	UFUNCTION(BlueprintCallable, Category="Ability|MeleeWeapon")
	ABaseWeaponInstance* GetWeaponInstance();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	void AbilityFinish();
protected:
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Ability|MeleeWeapon")
	UAnimMontage* MontageToPlay;
	
	UPROPERTY()
	TWeakObjectPtr<ACharacter> Owner;

	FGameplayAbilitySpecHandle mAbilitySpecHandle;
	const FGameplayAbilityActorInfo* mActorInfo;
	FGameplayAbilityActivationInfo mActivationInfo;
	
};
