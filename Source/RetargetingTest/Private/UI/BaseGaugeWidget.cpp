// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/BaseGaugeWidget.h"

#include "Components/ProgressBar.h"

void UBaseGaugeWidget::NativeConstruct()
{
	Super::NativeConstruct();
}



void UBaseGaugeWidget::UpdateHPWidget(float NewHPPercent)
{
	//보간을 사용해 HP를 조절해야하는데.. 아직 구현은 블루프린트에 되어있음.
}

