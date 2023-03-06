// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/MonsterHPWidget.h"

#include "VectorTypes.h"
#include "Components/ProgressBar.h"
#include "RetargetingTest/Component/Public/BaseMonsterStatComponent.h"

void UMonsterHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
}


/**
 * 체력이 수정된다면 바뀐 Hp를 프로그래스바에 적용시킵니다.
 */
void UMonsterHPWidget::UpdateHPWidget()
{
	const float NewHp = CurrentActorStat->GetNewHpPercent();
	HpProgressBar->SetPercent(NewHp);
	
	
}
 