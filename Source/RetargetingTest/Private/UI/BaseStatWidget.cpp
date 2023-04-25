// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/BaseStatWidget.h"

#include "Components/ProgressBar.h"
#include "RetargetingTest/Public/Component//BaseStatComponent.h"

void UBaseStatWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HpProgressBar=Cast<UProgressBar>(GetWidgetFromName("PB_HPBar"));

}

/**
 * 새로운 액터의 스탯컴포넌트를 받아 바인딩합니다.
 * @param NewActorStat-액터의 스탯컴포넌트가 들어옵니다.
 */
void UBaseStatWidget::BindActorStat(UBaseStatComponent* NewActorStat)
{
	CurrentActorStat=NewActorStat;
	if(CurrentActorStat!=nullptr)
	CurrentActorStat->OnHPChangedDelegate.AddUObject(this,&UBaseStatWidget::UpdateHPWidget);
}

void UBaseStatWidget::UpdateHPWidget()
{
	//보간을 사용해 HP를 조절해야하는데.. 아직 구현은 블루프린트에 되어있음.
}

