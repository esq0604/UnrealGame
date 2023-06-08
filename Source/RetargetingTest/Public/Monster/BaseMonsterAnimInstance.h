// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseMonsterAnimInstance.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckSignature);
UCLASS()
class RETARGETINGTEST_API UBaseMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBaseMonsterAnimInstance();
	
	void PlayDeadMontage();

private:


public:
	FOnAttackHitCheckSignature OnAttackHitCheckDelegate;
protected:
	UPROPERTY(BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UAnimMontage* mHitMontage;

	UPROPERTY(BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UAnimMontage* mDeadMontage;

	UPROPERTY(BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	float mSpeed;

	
private:
};
