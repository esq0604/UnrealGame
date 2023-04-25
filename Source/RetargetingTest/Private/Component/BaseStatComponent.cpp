// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Component/BaseStatComponent.h"


// Sets default values for this component's properties
UBaseStatComponent::UBaseStatComponent()
{
	
}

/**
 * 체력을 조정합니다. 피가 0이 된다면 델리게이트를 호출합니다.
 * @param NewHp - 변경될 체력이 들어옵니다.
 */
void UBaseStatComponent::SetHP(const float& NewHp)
{
	CurrentHpPercent=GetHPRatio(CurrentHp); //현재 피 퍼센트
	NewHpPercent=GetHPRatio(NewHp); //받아서 까인 피 퍼센트
	OnHPChangedDelegate.Broadcast(); //widget 처리 후
	CurrentHp=NewHp; //현재 피 갱신 
	if(CurrentHp<KINDA_SMALL_NUMBER)
	{
		CurrentHp =0.0f;
		OnHPIsZeroDelegate.Broadcast();
	}
}

/**
 * 프로그레스바에 체력의 퍼센트를 전달하기 위해 전체체력에 대한 현제 체력 퍼센트를 계산합니다.
 */
float UBaseStatComponent::GetHPRatio(const float& ChangedHP)
{
	return (MaxHp < KINDA_SMALL_NUMBER) ? 0.0f : (ChangedHP / MaxHp); 

}

/**
 * 데미지를 받았을시 실행됩니다. 체력을 조정하도록 합니다.
 * @param Damage - 받은 데미지의 양이 들어옵니다.
 */
void UBaseStatComponent::SufferDamage(const float& Damage)
{
	SetHP(FMath::Clamp<float>(CurrentHp-Damage,0.0f,MaxHp));
}

/**
 * AttackDamage의 Getter입니다.
 */
float UBaseStatComponent::GetAttackDamage() const
{
	return AttackDamage;
}

/**
 * CurrentHpPercent의 Getter입니다.
 */
float UBaseStatComponent::GetCurrentHpPercent() const
{
	return CurrentHpPercent;
}

/**
 * NewHpPercent의 Getter입니다.
 */
float UBaseStatComponent::GetNewHpPercent() const
{
	return NewHpPercent;
}
