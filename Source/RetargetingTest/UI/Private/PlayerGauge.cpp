// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/PlayerGauge.h"

#include "Components/ProgressBar.h"
#include "RetargetingTest/Component/Public/BasePlayerStatComponent.h"
void UPlayerGauge::NativeConstruct()
{
	Super::NativeConstruct();
	Stamina=Cast<UProgressBar>(GetWidgetFromName("PB_Stamina"));
}


/**
 * 현재 블루프린트의 Tick 이벤트에 구현해놨고, 구현해야 하는 함수입니다.
 */
void UPlayerGauge::UpdateHPWidget()
{
}

void UPlayerGauge::UpdateStaminaWidget()
{
	UBasePlayerStatComponent* PlayerStatComponent=Cast<UBasePlayerStatComponent>(CurrentActorStat);
	Stamina->SetPercent(PlayerStatComponent->GetCurrentStaminaPercent());
}

void UPlayerGauge::BindActorStat(UBaseStatComponent* NewActorStat)
{
	Super::BindActorStat(NewActorStat);
	UBasePlayerStatComponent* PlayerStatComponent = Cast<UBasePlayerStatComponent>(NewActorStat);
	PlayerStatComponent->OnStaminaChangedDelegate.AddUObject(this,&UPlayerGauge::UpdateStaminaWidget);
}


