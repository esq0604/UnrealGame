// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/MonsterHPWidget.h"

#include "VectorTypes.h"
#include "Components/ProgressBar.h"
#include "RetargetingTest/Component/Public/MonsterStatComponent.h"

void UMonsterHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	mHPProgressBar=Cast<UProgressBar>(GetWidgetFromName("PB_HPBar"));
}

/**
 * 위젯과 체력 컴포넌트를 델리게이트를 통해 바인딩하여 체력이 수정되면 UpdateWidget함수가 호출됩니다.
 * @param NewMonsterStat - 바인딩할 스탯컴포넌트가 들어옵니다.
 */
void UMonsterHPWidget::BindMonsterStat(UMonsterStatComponent* NewMonsterStat)
{
	CurrentMonsterStat = NewMonsterStat;
	NewMonsterStat->OnHPChangedDelegate.AddUObject(this,&UMonsterHPWidget::UpdateHPWidget);
}
/**
 * 체력이 수정된다면 바뀐 Hp를 프로그래스바에 적용시킵니다.
 */
void UMonsterHPWidget::UpdateHPWidget()
{
	float CurrentHP = CurrentMonsterStat->GetCurrentHpPercent();
	const float NewHp = CurrentMonsterStat->GetReducedHpPercent();
	
	mHPProgressBar->SetPercent(NewHp);
	
	
}
 