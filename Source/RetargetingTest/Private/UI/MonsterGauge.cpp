// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/MonsterGauge.h"

#include "Components/ProgressBar.h"
#include "UI/GaugeBar.h"


void UMonsterGauge::NativeConstruct()
{
	Super::NativeConstruct();
	bCanChildrenBeAccessible=true;

	//bHasScriptImplementedTick=true;
}

void UMonsterGauge::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	//현재 체력퍼센트가 감소된 체력퍼센트보다 크거나 같을때까지 
	// CurrentTime+=InDeltaTime;
	// if(CurrentTime>=LerpTime)W
	// {
	// 	CurrentTime=LerpTime;
	// }
	//
	// const float LerpHpValue=FMath::Lerp(mOldHpPercent,mNewHpPercent,CurrentTime/LerpTime);
	//
	//HpProgressBar->SetPercent(LerpHpValue);
}

void UMonsterGauge::UpdateHPWidget(float NewHPPercent, float OldHPPercent)
{
	mNewHpPercent=NewHPPercent;
	mOldHpPercent=OldHPPercent;
	
	HPGaugeBar->UpdateWidget(mNewHpPercent,mOldHpPercent);
}

void UMonsterGauge::Init()
{
	HPGaugeBar->UpdateWidget(1.0f,1.0f);
}
 