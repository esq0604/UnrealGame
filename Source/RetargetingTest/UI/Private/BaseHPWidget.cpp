// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/BaseHPWidget.h"

#include "Components/ProgressBar.h"
#include "RetargetingTest/Component/Public/BaseStatComponent.h"

void UBaseHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HpProgressBar=Cast<UProgressBar>(GetWidgetFromName("PB_HPBar"));

}

/**
 * 새로운 액터의 스탯컴포넌트를 받아 바인딩합니다.
 * @param 액터의 스탯컴포넌트가 들어옵니다.
 */
void UBaseHPWidget::BindActorStat(UBaseStatComponent* NewActorStat)
{
	CurrentActorStat=NewActorStat;
	CurrentActorStat->OnHPChangedDelegate.AddUObject(this,&UBaseHPWidget::UpdateHPWidget);
}

void UBaseHPWidget::UpdateHPWidget()
{
	//보간을 사용해 HP를 조절해야하는데.. 아직 구현은 블루프린트에 되어있음.
}

