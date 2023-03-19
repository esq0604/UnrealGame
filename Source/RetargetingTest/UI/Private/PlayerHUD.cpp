// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/PlayerHUD.h"

#include "Kismet/GameplayStatics.h"
#include "RetargetingTest/Component/Public/BasePlayerStatComponent.h"
#include "RetargetingTest/UI/Public/Inventory.h"
#include "RetargetingTest/UI/Public/PlayerGauge.h"
#include "RetargetingTest/UI/Public/QuickSlot.h"

/**
 * 플레이어 HUD의 초기화부분입니다.
 * 플레이어의 체력,스태미나를 스탯과 바인딩하고, 퀵슬롯과 인벤토리를 초기화합니다.
 */
void UPlayerHUD::Init()
{
	if(Character!=nullptr)
	{
		Gauge->BindActorStat(Character->GetStatComponent());

		QuickSlot->SetCharacter(Character);
		QuickSlot->Init();
	
		Inventory->SetCharacter(Character);
		Inventory->SetVisibility(ESlateVisibility::Hidden);
		Inventory->Init();
	}
}

UPlayerGauge* UPlayerHUD::GetGauge() const
{
	return Gauge;
}

UQuickSlot* UPlayerHUD::GetQuickSlot() const
{
	return QuickSlot;
}

UInventory* UPlayerHUD::GetInventory() const
{
	return Inventory;
}

void UPlayerHUD::SetCharacter(ARetargetingTestCharacter* NewCharater)
{
	Character = NewCharater;
}

/**
 * 인벤토리 토글함수입니다. 현재 보이고있으면 안보이게하고, 안보이고있다면 보이도록합니다.
 */
void UPlayerHUD::ToggleInventory()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);

	if(Inventory->GetVisibility()==ESlateVisibility::Hidden)
	{
		Inventory->SetVisibility(ESlateVisibility::Visible);
		PlayerController->SetShowMouseCursor(true);
	}
	else
	{
		Inventory->SetVisibility(ESlateVisibility::Hidden);
		PlayerController->SetShowMouseCursor(false);
	}
	
}
