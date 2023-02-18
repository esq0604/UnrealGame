// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharaterAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMontageEndedDelegate,UAnimMontage* Montage, bool bInterrupted);
/**
 * 
 */
 class ARetargetingTestCharacter;
UCLASS()
class RETARGETINGTEST_API UCharaterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	UCharaterAnimInstance(const FObjectInitializer& ObjectInitializer);

	void PlayAttackMontage();
protected:
	virtual void NativeBeginPlay() override;
private:
	UFUNCTION()
	void AnimNotify_SaveAttack();

	UFUNCTION()
	void AnimNotify_EnableCollision();
	
	UFUNCTION()
	void AnimNotify_DisableCollision();
public:
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FOnMontageEndedDelegate OnMontageEnded;
protected:
	
private:
	UPROPERTY()
	UAnimMontage* AttackMontage;


};
