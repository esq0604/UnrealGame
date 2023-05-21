// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/PlayerGauge.h"
#include "Player/CharacterBase.h"
#include "Components/ProgressBar.h"
#include "Player/PlayerStateBase.h"


void UPlayerGauge::NativeConstruct()
{
	Super::NativeConstruct();
	bCanChildrenBeAccessible=true;
	// StaminaProgressBar=Cast<UProgressBar>(GetWidgetFromName("PB_Stamina"));
	// HpProgressBar=Cast<UProgressBar>(GetWidgetFromName("PB_HPBar"));
}

/**
 * @param NewHPPercent : HPProgressBar의 설정될 퍼센트값이 들어옵니다.
 */
void UPlayerGauge::UpdateHPWidget(float NewHPPercent)
{
	if(HpProgressBar!=nullptr)
	HpProgressBar->SetPercent(NewHPPercent);
}

void UPlayerGauge::UpdateStaminaWidget(float NewStaminaPercent)
{
	if(StaminaProgressBar!=nullptr)
	StaminaProgressBar->SetPercent(NewStaminaPercent);
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Stam nullptr"));
	}
}

void UPlayerGauge::SetCharacter(ACharacterBase* NewPlayer)
{
	Player=NewPlayer;
}

void UPlayerGauge::Init()
{
	if(Player!=nullptr)
	{
		const APlayerStateBase* LocalPS=Cast<APlayerStateBase>(Player->GetPlayerState());
		if(LocalPS!=nullptr)
		{
			if(LocalPS->GetAttributes()!=nullptr)
			{
				 const float Health=Player->GetAttributes()->GetHealth();
				 const float MaxHealth=Player->GetAttributes()->GetMaxHealth();
				 const float Stamina =Player->GetAttributes()->GetStamina();
				 const float MaxStamina =Player->GetAttributes()->GetMaxStamina();

				if(HpProgressBar!=nullptr)
					UpdateHPWidget(Health/MaxHealth);
				else
				{
					UE_LOG(LogTemp,Warning,TEXT("PlayerGauge Init : HpProgressBar nullptr"));
				}
				if(StaminaProgressBar!=nullptr)
					UpdateStaminaWidget(Stamina/MaxStamina);
				else
				{
					UE_LOG(LogTemp,Warning,TEXT("PlayerGauge Init : StaminaProgressBar nullptr"));
				}
			}
			else
			{
				UE_LOG(LogTemp,Warning,TEXT("PlayerGauge Init : LocalPS->GetAttributes() nullptr"));
			}
		}
		 else
		 {
		 	UE_LOG(LogTemp,Warning,TEXT("PlayerGauge Init : LocalPS nullptr"));
		 }
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("PlayerGauge Init : Player nullptr"));
	}
}


