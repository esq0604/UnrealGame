// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/PlayerHUD.h"

#include "Kismet/GameplayStatics.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"
#include "RetargetingTest/Public/UI/Inventory.h"
#include "RetargetingTest/Public/UI/QuickSlot.h"
#include "UI/GaugeBar.h"


/**
 * 플레이어 HUD의 초기화부분입니다.
 * 플레이어의 체력,스태미나를 스탯과 바인딩하고, 퀵슬롯과 인벤토리를 초기화합니다.
 */
void UPlayerHUD::Init()
{
	
	if(Player!=nullptr)
	{
		//Gauge->BindActorStat(Character->GetStatComponent());
		HPGauge->SetCharacter(Player);
		StaminaGauge->SetCharacter(Player);
		
		QuickSlot->SetCharacter(Player);
		QuickSlot->Init();
	
		Inventory->SetCharacter(Player);
		Inventory->SetVisibility(ESlateVisibility::Hidden);
		Inventory->Init();
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

UQuickSlot* UPlayerHUD::GetQuickSlot() const
{
	return QuickSlot;
}

UInventory* UPlayerHUD::GetInventory() const
{
	return Inventory;
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

void UPlayerHUD::SetQuickSlot(UQuickSlot* NewQuickSlot)
{
	QuickSlot=NewQuickSlot;
}

void UPlayerHUD::SetInventory(UInventory* NewInventory)
{
	Inventory=NewInventory;
}


void UPlayerHUD::SetCharacter(ACharacter* NewPlayer)
{
	Player = Cast<ACharacterBase>(NewPlayer);
}

/**
 * 인벤토리 토글함수입니다. 현재 보이고있으면 안보이게하고, 안보이고있다면 보이도록합니다.
 */
void UPlayerHUD::ToggleInventory()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);

	if(Inventory->GetVisibility()==ESlateVisibility::Collapsed)
	{
		Inventory->SetVisibility(ESlateVisibility::Visible);
		PlayerController->SetShowMouseCursor(true);
	}
	else
	{
		Inventory->SetVisibility(ESlateVisibility::Collapsed);
		PlayerController->SetShowMouseCursor(false);
	}
	
}