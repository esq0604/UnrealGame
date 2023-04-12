// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Player/Public/CharaterAnimInstance.h"

#include "GameplayTagContainer.h"
#include "../Public//CharacterBase.h"
#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"
UCharaterAnimInstance::UCharaterAnimInstance(const FObjectInitializer& ObjectInitializer)
{
}

void UCharaterAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage,1.0f);
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

void UCharaterAnimInstance::AnimNotify_SaveAttack()
{
	
}

/**
 * 공격 몽타주에 설정된 노티파이 입니다. 플레이어의 AttackHitCheck와 바인딩되어있습니다.
 */
void UCharaterAnimInstance::AnimNotify_AttackHitCheck()
{
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
 * TODO: 현재는 Dodge만 가능하지만 추후 노티파이에서 FGameplayTag를 변수로 받아. 다른 몽타주에도 적용해야합니다.
 * 애니메이션이 시작 됬을시 다른 스테이트로 변경하지 못하도록 변수를 설정합니다.
 */
void UCharaterAnimInstance::AnimNotify_StateStart()
{
	
//	OwnerCharacter->GetStateManagerComponent()->SetCurrentActiveState(OwnerCharacter->GetStateManagerComponent()->GetStateOfGameplayTag(FGameplayTag::RequestGameplayTag("State.Dodge")));
//	OwnerCharacter->GetStateManagerComponent()->SetCanChangeState(false);

}

/**
 * 애니메이션이 끝났을시 다른 스테이트로 변경될 수 있도록 변수를 설정합니다.
 */
void UCharaterAnimInstance::AnimNotify_StateEnd()
{
//	OwnerCharacter->GetStateManagerComponent()->SetCanChangeState(true);
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




