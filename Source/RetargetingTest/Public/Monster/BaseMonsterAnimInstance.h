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

	UFUNCTION()
	void PlayDeadMontage();


private:
	UFUNCTION()
	void DeadMontageEnded(UAnimMontage* Montage, bool bInterrupted);

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> mHitMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> mDeadMontage;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	float mSpeed;

private:
};
