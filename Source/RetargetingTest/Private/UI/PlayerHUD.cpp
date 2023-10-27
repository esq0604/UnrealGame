// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/PlayerHUD.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"
#include "RetargetingTest/Public/UI/InventoryUI.h"
#include "RetargetingTest/Public/UI/QuickSlotUI.h"
#include "UI/EquipmentUI.h"
#include "UI/GaugeBar.h"


/**
 * 플레이어 HUD의 초기화부분입니다.
 * 플레이어의 체력,스태미나를 스탯과 바인딩하고, 퀵슬롯과 인벤토리를 초기화합니다.
 */
void UPlayerHUD::Init()
{
	
	if(Player!=nullptr)
	{
		HPGauge->SetCharacter(Player);
		HPGauge->SetType(EGaugeType::HP);
		StaminaGauge->SetCharacter(Player);
		StaminaGauge->SetType(EGaugeType::Stamina);
		
		QuickSlot->SetInventoryComponent(Player->GetInventoryManagerComponent());
		QuickSlot->Init();
	}
}

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

}

UGaugeBar* UPlayerHUD::GetGauge(EGaugeType Type) const
{
	if(Type==EGaugeType::HP)
		return HPGauge;
	else if(Type == EGaugeType::Stamina)
		return StaminaGauge;

	return nullptr;
}

UQuickSlotUI* UPlayerHUD::GetQuickSlot() const
{
	return QuickSlot;
}

void UPlayerHUD::SetGauge(UGaugeBar* NewGauge,EGaugeType Type)
{
	if(Type == EGaugeType::HP)
	{
		HPGauge=NewGauge;
		HPGauge->SetType(Type);
	}
	else if(Type == EGaugeType::Stamina)
	{
		StaminaGauge=NewGauge;
		StaminaGauge->SetType(Type);
	}	
}

void UPlayerHUD::SetQuickSlot(UQuickSlotUI* NewQuickSlot)
{
	QuickSlot=NewQuickSlot;
}


void UPlayerHUD::SetCharacter(ACharacter* NewPlayer)
{
	Player = Cast<ACharacterBase>(NewPlayer);
}

FReply UPlayerHUD::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

/**
 * 인벤토리 토글입니다. 현재 보이고있으면 안보이게하고, 안보이고있다면 보이도록합니다.
 */


