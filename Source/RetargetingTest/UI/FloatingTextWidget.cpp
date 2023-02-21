// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingTextWidget.h"
#include <string>

#include "Components/TextBlock.h"

void UFloatingTextWidget::NativeConstruct()
{
	Super::NativeConstruct();
	DamageText=Cast<UTextBlock>(GetWidgetFromName("FloatingDamage"));

	//float f = 100;
	//FString FS=FString::SanitizeFloat(f);
	//DamageText->SetText(FText::FromString(FS)); 
	
	//DamageText->
}
