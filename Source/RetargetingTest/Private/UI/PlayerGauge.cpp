// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/PlayerGauge.h"

#include "FrameTypes.h"
#include "Attribute/CharacterAttributeSetBase.h"
#include "Player/CharacterBase.h"
#include "Components/ProgressBar.h"
#include "Player/PlayerStateBase.h"
#include "Math/UnrealMathUtility.h"


void UPlayerGauge::NativeConstruct()
{
	Super::NativeConstruct();
	bCanChildrenBeAccessible=true;
	bHasScriptImplementedTick=true;
}

void UPlayerGauge::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	//현재 체력퍼센트가 감소된 체력퍼센트보다 크거나 같을때까지 
	CurrentTime+=InDeltaTime;
	if(CurrentTime>=LerpTime)
	{
		CurrentTime=LerpTime;
	}
	
	const float LerpHpValue=FMath::Lerp(mOldHpPercent,mNewHpPercent,CurrentTime/LerpTime);
	const float LerpStaminaValue = FMath::Lerp(mOldStaminaPercent,mNewStaminaPercent,CurrentTime/LerpTime);

	if(mChangeHp)
	{
		UE_LOG(LogTemp,Warning,TEXT("Lerp Hp val %f"),LerpHpValue);
		LerpHpValue<=0.f ? HpProgressBar->SetPercent(0.f) : HpProgressBar->SetPercent(LerpHpValue);
		mChangeHp=false;
	}
	else if(mChangeStam)
	{
		StaminaProgressBar->SetPercent(LerpStaminaValue);
		mChangeStam=false;
	}
}

/**
 * @param NewHPPercent : HPProgressBar의 설정될 퍼센트값이 들어옵니다.
 */
void UPlayerGauge::UpdateHPWidget(float NewHPPercent,float OldHPPercent)
{
	mNewHpPercent=NewHPPercent;
	mOldHpPercent=OldHPPercent;
	mChangeHp=true;
	CurrentTime=0;
}

void UPlayerGauge::UpdateStaminaWidget(float NewStamPercent,float OldStamPercent)
{
	mNewStaminaPercent=NewStamPercent;
	mOldStaminaPercent=OldStamPercent;
	mChangeStam=true;
	CurrentTime=0;
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
				const float Stamina =Player->GetAttributes()->GetMana();
				const float MaxStamina =Player->GetAttributes()->GetMaxMana();

				UpdateHPWidget(Health/MaxHealth,Health/MaxHealth);
				UpdateStaminaWidget(Stamina/MaxStamina,Stamina/MaxStamina);
			}
		}
	}
}
