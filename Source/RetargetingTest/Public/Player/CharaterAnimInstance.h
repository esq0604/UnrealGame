// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AbilitySystemInterface.h"

#include "CharaterAnimInstance.generated.h"



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

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);
	
	virtual void NativeInitializeAnimation() override;
	UFUNCTION(BlueprintCallable)
	bool  GetIsBlocking() const;

	UFUNCTION(BlueprintCallable)
	void SetIsBlocking(bool newIsBlocking);
protected:
	virtual void NativeBeginPlay() override;

protected:
	//handle turning in place variables
	void TurnInPlace();

	//Handle calculations for leaning while running
	void Lean(float DeltaTime);
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Movement", meta=(AllowPrivateAccess="true"))
	ACharacterBase* OwnerCharacter;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	bool IsBlocking;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Movement", meta=(AllowPrivateAccess=true))
	float Speed;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Movement", meta=(AllowPrivateAccess=true))
	bool bIsInAir;
 
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Movement", meta=(AllowPrivateAccess=true))
	bool bIsAccelerating;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Movement", meta=(AllowPrivateAccess=true))
	float MovementOffsetYaw;

	//멈추기전 프레임의 OffsetYaw를 구합니다.
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Movement", meta=(AllowPrivateAccess=true))
	float LastMovementOffsetYaw;

	//yaw of the character this frame
	float TurnInPlaceCharacterYaw;

	//yaw of the character the previous frame
	float TurnInPlaceCharacterYawLastFrame;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Turn In Place", meta=(AllowPrivateAccess=true))
	float RootYawOffset;

	//Rotation curve value this frame
	float RotationCurve;
	//Rotation curve value last frame
	float RotationCurveLastFrame;

	//Character Yaw this frame; Only Update when standing still
	FRotator CharacterRotation;
	//Character Yaw last frame; 
	FRotator CharacterRotationLastFrame;

	//Yaw delta used for leaning in the running blendspace
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category=Lean, meta =(AllowPrivateAccess=true))
	float YawDelta;
};
