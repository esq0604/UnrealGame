// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AbilitySystemInterface.h"

#include "CharaterAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
//DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMontageEndedDelegate,UAnimMontage* , bool);
DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);


/**
 * 
 */
 class ACharacterBase;
UCLASS()
class RETARGETINGTEST_API UCharaterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	UCharaterAnimInstance(const FObjectInitializer& ObjectInitializer);

	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 NewSection);

	UFUNCTION(BlueprintCallable)
	bool GetIsBlocking() const;

	UFUNCTION(BlueprintCallable)
	void SetIsBlocking(bool newIsBlocking);
protected:
	virtual void NativeBeginPlay() override;
	
public :
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FOnNextAttackCheckDelegate OnNextAttackHitCheck;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UAnimMontage* AttackMontage;
protected:

private:
	UPROPERTY()
	ACharacterBase* OwnerCharacter;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	bool IsBlocking;



};
