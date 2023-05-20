// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/BaseStatWidget.h"

#include "Components/ProgressBar.h"

void UBaseStatWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HpProgressBar=Cast<UProgressBar>(GetWidgetFromName("PB_HPBar"));

}



void UBaseStatWidget::UpdateHPWidget()
{
	//보간을 사용해 HP를 조절해야하는데.. 아직 구현은 블루프린트에 되어있음.
}

