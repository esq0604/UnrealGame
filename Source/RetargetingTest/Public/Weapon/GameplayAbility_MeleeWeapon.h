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

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
protected:
	void PerformTrace(OUT TArray<FHitResult>& OutHits);

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	FHitResult mHitResult;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="MeleeWeapon|Initialize")
	float mRadius;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="MeleeWeapon|Initialize")
	float mHalfHeight;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="MeleeWeapon|Initialize")
	TArray<TEnumAsByte<EObjectTypeQuery>> mTraceObjectType;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Collision|Initialize")
	TArray<AActor*> mTraceActorToIgnore;
	
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	UPROPERTY()
	TWeakObjectPtr<ACharacter> Owner;
};
