// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterWidget.h"

#include "Components/ProgressBar.h"
#include "RetargetingTest/Component/MonsterStatComponent.h"

void UMonsterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	mHPProgressBar=Cast<UProgressBar>(GetWidgetFromName("PB_HPBar"));
}

void UMonsterWidget::BindMonsterStat(UMonsterStatComponent* NewMonsterStat)
{
	CurrentMonsterStat = NewMonsterStat;
	NewMonsterStat->OnHPChanged.AddUObject(this,&UMonsterWidget::UpdateHPWidget);
}

void UMonsterWidget::UpdateHPWidget()
{
	mHPProgressBar->SetPercent(CurrentMonsterStat->GetHPRatio());
}
 