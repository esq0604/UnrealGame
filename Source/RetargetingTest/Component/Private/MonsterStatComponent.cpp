// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/MonsterStatComponent.h"


// Sets default values for this component's properties
UMonsterStatComponent::UMonsterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent=true;

}

float UMonsterStatComponent::GetCurrentHpPercent() const
{
	return CurrentHpPercent;
}

float UMonsterStatComponent::GetReducedHpPercent() const
{
	return ReducedHpPercent;
}

void UMonsterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetHP(MaxHP);
}

// Called when the game starts
void UMonsterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMonsterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/**
 * 몬스터가 피해를 입었을시 SetHP를 이용해 체력을 수정합니다.
 * @param Damage - 받은 데미지가 들어옵니다.
 */
void UMonsterStatComponent::GetDamaged(const float& Damage)
{
	SetHP(FMath::Clamp<float>(CurrentHp-Damage,0.0f,MaxHP));
}

/** 현재 hp를 수정하고, 바인딩된 델리게이트를 호출합니다.
 *	OnHPChangedDelegate - 몬스터의 체력 위젯과 바인딩되어 프로그래스바를 변합니다.
 *	OnHPIsZeroDelegate - 체력이 0이 된다면 몬스터가 죽게됩니다.
 * @param NewHP - 바뀌게 될 Hp가 들어옵니다.
 */
void UMonsterStatComponent::SetHP(const float& NewHP)
{
	CurrentHpPercent=GetHPRatio(CurrentHp);
	ReducedHp=NewHP;
	ReducedHpPercent=GetHPRatio(ReducedHp);
	OnHPChangedDelegate.Broadcast();
	CurrentHp=NewHP;

	if(ReducedHp<KINDA_SMALL_NUMBER)
	{
		ReducedHp =0.0f;
		OnHPIsZeroDelegate.Broadcast();
	}
}

/**
 *  체력을 받아서 최대 체력에 대한 퍼센트를 반환합니다.
 *  @param HP - 최대 체력에 대한 퍼센트를 알고싶은 HP가 들어갑니다.
 */
float UMonsterStatComponent::GetHPRatio(const float& HP) const
{
	return (MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (HP / MaxHP); 
}

float UMonsterStatComponent::GetAttackDamage() const
{
	return AttackDamage;

}
