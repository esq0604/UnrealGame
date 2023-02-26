// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHPWidget.h"

#include "Components/ProgressBar.h"
#include "../Component/PlayerStatComponent.h"
void UPlayerHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	mHPProgressBar=Cast<UProgressBar>(GetWidgetFromName("PB_HPBar"));
}

void UPlayerHPWidget::BindCharacterStat(UPlayerStatComponent* NewCharaterStat)
{
	CurrentCharacterStat=NewCharaterStat;
	CurrentCharacterStat->OnHPChanged.AddUObject(this,&UPlayerHPWidget::UpdateHPWidget);
}

void UPlayerHPWidget::UpdateHPWidget()
{
	UE_LOG(LogTemp,Warning,TEXT("Update Player HP bar widget"));
	mHPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
}


