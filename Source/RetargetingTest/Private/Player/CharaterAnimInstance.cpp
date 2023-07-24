// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Player/CharaterAnimInstance.h"
#include "GameplayTagContainer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"
#include "Kismet/KismetMathLibrary.h"

UCharaterAnimInstance::UCharaterAnimInstance(const FObjectInitializer& ObjectInitializer)
	:Speed(0.f),bIsInAir(false),bIsAccelerating(false),MovementOffsetYaw(0.f),LastMovementOffsetYaw(0.f),CharacterYaw(0.f),
	CharacterYawLastFrame(0.f),RootYawOffset(0.f)
{
}

void UCharaterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if(OwnerCharacter ==nullptr)
	{
		OwnerCharacter=Cast<ACharacterBase>(TryGetPawnOwner());
	}

	if(OwnerCharacter)
	{
		FVector Velocity{OwnerCharacter->GetVelocity()};
		Velocity.Z=0;
		Speed=Velocity.Size();
		bIsInAir = OwnerCharacter->GetCharacterMovement()->IsFalling();

		if(OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() >0.f)
		{
			bIsAccelerating=true;
		}
		else
		{
			bIsAccelerating=false;
		}
		const FRotator AimRotation = OwnerCharacter->GetBaseAimRotation();
		const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(OwnerCharacter->GetVelocity());
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation,AimRotation).Yaw;

		if(OwnerCharacter->GetVelocity().Size()>0.f)
		{
			LastMovementOffsetYaw=MovementOffsetYaw;
		}

		// FString MovementOffsetYawText=FString::Printf(TEXT("MovementOffsetYaw : %f"),MovementOffsetYaw);
		// if(GEngine)
		// {
		// 	GEngine->AddOnScreenDebugMessage(1,0.f,FColor::White,MovementOffsetYawText);
		// }
	}
	TurnInPlace();

}

/**
 * CharacterAnimInstance를 사용하고 있는 캐릭터에 대해서 받아옵니다.
 */
void UCharaterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter=Cast<ACharacterBase>(GetOwningActor());
	//Montage_SetEndDelegate(OnMontageEnded);
}

void UCharaterAnimInstance::TurnInPlace()
{
	if(OwnerCharacter==nullptr) return;
	if(Speed>0)
	{
		//Don't want to turn in place charater is moving
		RootYawOffset=0.f;
		CharacterYaw=OwnerCharacter->GetActorRotation().Yaw;
		CharacterYawLastFrame=CharacterYaw;
		RotationCurve=0.f;
		RotationCurveLastFrame=0.f;
	}
	else
	{
		CharacterYawLastFrame=CharacterYaw;
		CharacterYaw=OwnerCharacter->GetActorRotation().Yaw;

		const float YawDelta{ CharacterYaw-CharacterYawLastFrame };

		//root yaw offset, update and clamped to [-180,180]
		RootYawOffset =UKismetMathLibrary::NormalizeAxis(RootYawOffset - YawDelta);

		// 1.0f if turning , 0.0 if not
		const float Turning{GetCurveValue(TEXT("Turning"))};
		if(Turning>0)
		{
			RotationCurveLastFrame = RotationCurve;
			RotationCurve = GetCurveValue(TEXT("Rotation"));
			const float DeltaRotation{RotationCurve - RotationCurveLastFrame};

			//rootyawoffset > 0 , ->Turning Left, RootYawOffset <0, ->Turning Right
			RootYawOffset > 0 ? RootYawOffset -= DeltaRotation : RootYawOffset += DeltaRotation;

			const float ABSRootYawOffset{FMath::Abs(RootYawOffset)};
			if(ABSRootYawOffset >90.f)
			{
				const float YawExcess{ABSRootYawOffset - 90.0f};
				RootYawOffset > 0 ? RootYawOffset -= YawExcess : RootYawOffset += YawExcess;
			}
		}

		
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1,-1,FColor::Blue, FString::Printf(TEXT("CharacterYaw : %f"),CharacterYaw));
			GEngine->AddOnScreenDebugMessage(2,-1,FColor::Red, FString::Printf(TEXT("RootYawOffset : %f"),RootYawOffset));
		}
	}
	
}

void UCharaterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwnerCharacter=Cast<ACharacterBase>(TryGetPawnOwner());
	
}

bool UCharaterAnimInstance::GetIsBlocking() const
{
	return IsBlocking;
}

void UCharaterAnimInstance::SetIsBlocking(bool newIsBlocking)
{
	IsBlocking=newIsBlocking;
}





