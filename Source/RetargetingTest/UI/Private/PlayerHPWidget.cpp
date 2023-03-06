// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/PlayerHPWidget.h"

#include "Components/ProgressBar.h"
#include "RetargetingTest/Component/Public/PlayerStatComponent.h"
void UPlayerHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	mHPProgressBar=Cast<UProgressBar>(GetWidgetFromName("PB_HPBar"));
}

/**
 * 캐릭터의 스텟과 바인딩하여 체력이 변경되면 델리게이트를 호출하도록 합니다.
 * @param NewCharaterStat - 플레이어의 체력 컴포넌트가 들어옵니다
 */
void UPlayerHPWidget::BindCharacterStat(UPlayerStatComponent* NewCharaterStat)
{
	CurrentCharacterStat=NewCharaterStat;
	CurrentCharacterStat->OnHPChanged.AddUObject(this,&UPlayerHPWidget::UpdateHPWidget);
}

/**
 * 현재 블루프린트의 Tick 이벤트에 구현해놨고, 구현해야 하는 함수입니다.
 */
void UPlayerHPWidget::UpdateHPWidget()
{
	
}


