// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/FloatingTextWidget.h"

#include <string>

#include "Components/TextBlock.h"

void UFloatingTextWidget::NativeConstruct()
{
	Super::NativeConstruct();
	DamageText=Cast<UTextBlock>(GetWidgetFromName("FloatingDamage"));
}
