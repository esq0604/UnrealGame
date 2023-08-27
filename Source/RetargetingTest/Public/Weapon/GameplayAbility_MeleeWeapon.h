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
	UGameplayAbility_MeleeWeapon(const FObjectInitializer& Initializer);
	
	UFUNCTION(BlueprintCallable, Category="Ability|MeleeWeapon")
	ABaseWeaponInstance* GetWeaponInstance();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


	UFUNCTION(BlueprintCallable)
	void AbilityFinish();

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayDamageEffect(FGameplayEventData Payload);

	UFUNCTION(BlueprintCallable)
	void SetHitResult(const FHitResult& HitResult);
protected:
	UFUNCTION(BlueprintCallable)
	void ActiveMontage();
	UFUNCTION(BlueprintCallable)
	void WaitGameplayEventForApplyDamageEffect();
protected:
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Ability|MeleeWeapon")
	TObjectPtr<UAnimMontage> MontageToPlay;
	
	UPROPERTY()
	TWeakObjectPtr<ACharacter> Owner;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Ability|MeleeWeapon")
	TSubclassOf<UGameplayEffect> mDamageGameplayEffectClass;

	// Ability Active Init
	FGameplayAbilitySpecHandle mAbilitySpecHandle;
	const FGameplayAbilityActorInfo* mActorInfo;
	FGameplayAbilityActivationInfo mActivationInfo;

	//HitResult for EffectContext
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FHitResult mHitResult;
};


