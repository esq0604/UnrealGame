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

	//현재 체력 퍼센트에서 감소한 체력퍼센트까지보간을 이용해 줄입니다.
	//UE_LOG(LogTemp,Warning,TEXT("CurrentHPPercent %f"),CurrentCharacterStat->GetCurrentHPPercent());
	//UE_LOG(LogTemp,Warning,TEXT("NewHPPercent %f"),CurrentCharacterStat->GetNewHPPercent());
	 // while(CurrentCharacterStat->GetCurrentHPPercent()>CurrentCharacterStat->GetNewHPPercent())
	 // {
	 // 	Percent=FMath::Lerp(CurrentCharacterStat->GetCurrentHPPercent(),CurrentCharacterStat->GetNewHPPercent(),0.1);
	 // 	//UE_LOG(LogTemp,Warning,TEXT("%f"),SettingHPPercent);
	 // 	mHPProgressBar->SetPercent(Percent);
	 // }
}


