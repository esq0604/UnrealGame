// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Player/Public/CharaterAnimInstance.h"

#include "../Public//RetargetingTestCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UCharaterAnimInstance::UCharaterAnimInstance(const FObjectInitializer& ObjectInitializer)
{
}

void UCharaterAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage,1.0f);
}



void UCharaterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	// character=Cast<ARetargetingTestCharacter>(GetOwningActor());
	// bIsTrunLeft=character->GetIsTurnLeft();
	// bIsTrunRight=character->GetIsTurnRight();
	//Montage_SetEndDelegate(OnMontageEnded);
}

void UCharaterAnimInstance::AnimNotify_SaveAttack()
{
	
}

/**
 * 공격 몽타주에 설정된 노티파이 입니다. 플레이어의 AttackHitCheck와 바인딩되어있습니다.
 */
void UCharaterAnimInstance::AnimNotify_AttackHitCheck()
{
	UE_LOG(LogTemp,Warning,TEXT("AttackHitCheck"));
	OnAttackHitCheck.Broadcast();
}

/**
 * 공격 몽타주에 설정된 노티파이 입니다. 다음 콤보 공격이 가능한지 체크하는 노티파이입니다.
 */
void UCharaterAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackHitCheck.Broadcast();
}

/**
 * 콤보 공격을 위해 다음 섹션으로 넘어갑니다.
 * @param NewSection - 새로운 섹션 번호를 받아 다음섹션으로 넘어갑니다.
 * @warning GetAttackMonatageSectionName과 같이 사용해야합니다.
 */
void UCharaterAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection),AttackMontage);
}

/**
 * 공격 몽타주에서 구분된 섹션을 넘어가기 위해 섹션이름을 가져오는 함수입니다.
 * @param Section - 다음 콤보 공격의 섹션 번호가 들어갑니다. 
 */
FName UCharaterAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"),Section));
}




