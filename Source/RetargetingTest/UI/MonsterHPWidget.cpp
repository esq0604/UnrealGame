// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHPWidget.h"

#include "VectorTypes.h"
#include "Components/ProgressBar.h"
#include "RetargetingTest/Component/MonsterStatComponent.h"

void UMonsterHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	mHPProgressBar=Cast<UProgressBar>(GetWidgetFromName("PB_HPBar"));
}

void UMonsterHPWidget::BindMonsterStat(UMonsterStatComponent* NewMonsterStat)
{
	CurrentMonsterStat = NewMonsterStat;
	NewMonsterStat->OnHPChanged.AddUObject(this,&UMonsterHPWidget::UpdateHPWidget);
}

void UMonsterHPWidget::UpdateHPWidget()
{
	
	mHPProgressBar->SetPercent(CurrentMonsterStat->GetHPRatio());
}
 