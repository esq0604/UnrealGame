// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharaterAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
//DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMontageEndedDelegate,UAnimMontage* , bool);
DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);


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
	void JumpToAttackMontageSection(int32 NewSection);

protected:
	virtual void NativeBeginPlay() override;
	
private:
	UFUNCTION()
	void AnimNotify_SaveAttack();
	
	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	UFUNCTION()
	void AnimNotify_StateStart();
	

	UFUNCTION()
	void AnimNotify_StateEnd();
	FName GetAttackMontageSectionName(int32 Section);

public :
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FOnNextAttackCheckDelegate OnNextAttackHitCheck;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UAnimMontage* AttackMontage;
protected:

private:
	UPROPERTY()
	ARetargetingTestCharacter* OwnerCharacter;



};
