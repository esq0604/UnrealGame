// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterWidget.h"

#include "Components/ProgressBar.h"

void UMonsterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	mHPProgressBar=Cast<UProgressBar>(GetWidgetFromName("PB_HPBar"));
}
 