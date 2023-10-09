// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_AllowPhyiscRotation.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimNotifyState_AllowPhyiscRotation::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                       float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ACharacter* Character =Cast<ACharacter>(MeshComp->GetOwner());
	if(Character)
	{
		Character->bUseControllerRotationYaw=false;
		UCharacterMovementComponent* CharacterMovementComp = Character->GetCharacterMovement();
		if(CharacterMovementComp)
		{
			CharacterMovementComp->bAllowPhysicsRotationDuringAnimRootMotion=true;
			CharacterMovementComp->bUseControllerDesiredRotation=false;
			CharacterMovementComp->RotationRate= FRotator(0,800.f,0);

			//TODO :타게팅모드인지에 따라 무브먼트회전방향으로 조정옵션을 활성화합니다.
			CharacterMovementComp->bOrientRotationToMovement=true;

		}
	}
}

void UAnimNotifyState_AllowPhyiscRotation::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	
	ACharacter* Character =Cast<ACharacter>(MeshComp->GetOwner());
	if(Character)
	{
		Character->bUseControllerRotationYaw=false;
		UCharacterMovementComponent* CharacterMovementComp = Character->GetCharacterMovement();
		if(CharacterMovementComp)
		{
			CharacterMovementComp->bAllowPhysicsRotationDuringAnimRootMotion=false;
			CharacterMovementComp->bOrientRotationToMovement=false;
			CharacterMovementComp->bUseControllerDesiredRotation=true;
			CharacterMovementComp->RotationRate= FRotator(0,300.f,0);

			//TODO :타게팅모드인지에 따라 무브먼트회전방향으로 조정옵션을 활성화합니다.
			CharacterMovementComp->bOrientRotationToMovement=true;
		}	
	}
}
