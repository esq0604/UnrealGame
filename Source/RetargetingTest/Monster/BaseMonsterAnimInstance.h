// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseMonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UBaseMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBaseMonsterAnimInstance();

	void PlayHitMontage();

	void PlayDeadMontage();
protected:
	UPROPERTY(BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UAnimMontage* mHitMontage;

	UPROPERTY(BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UAnimMontage* mDeadMontage;

	UPROPERTY(BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	float mSpeed;

	
private:
	
};
