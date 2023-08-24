// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerStateBase.h"

#include "AbilitySystemComponent.h"
#include "Ability/CharacterAbilitySystemComponent.h"
#include "Ability/CustomAbilitySystemComponent.h"
#include "Attribute/CharacterAttributeSetBase.h"
#include "Controller/MyPlayerController.h"
#include "UI/GaugeBar.h"
#include "UI/PlayerGauge.h"
#include "UI/PlayerHUD.h"

// Sets default values
APlayerStateBase::APlayerStateBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	Attributes = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("Attribute"));
}

// Called every frame
void APlayerStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UAbilitySystemComponent* APlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBaseAttributeSet* APlayerStateBase::GetAttributes() const
{
	return Attributes;
}

void APlayerStateBase::SetPlayerHUD(UPlayerHUD* NewPlayerHUD)
{
	PlayerHUD=NewPlayerHUD;
	
	//PlayerHUD->Child
}

// Called when the game starts or when spawned
void APlayerStateBase::BeginPlay()
{
	Super::BeginPlay();
	const AMyPlayerController*  PC= Cast<AMyPlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
	
	if(AbilitySystemComponent)
	{
		HealthChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute()).AddUObject(this,&APlayerStateBase::HealthChange);
		MaxHealthChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxHealthAttribute()).AddUObject(this,&APlayerStateBase::MaxHealthChange);
		ManaChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetManaAttribute()).AddUObject(this,&APlayerStateBase::StaminaChange);
		MaxManaChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxManaAttribute()).AddUObject(this,&APlayerStateBase::MaxManaChange);
	}

	PlayerHUD=PC->GetPlayerHUD();
}

/**
 * 어트리뷰트의 변경에 대한 호출 함수 입니다.
 * @param Data : 변경된 속성의 값이 들어옵니다.
 */
void APlayerStateBase::HealthChange(const FOnAttributeChangeData& Data)
{
	const float NewHealthPercent=Data.NewValue/Attributes->GetMaxHealth();
	const float OldHealthPercent=Data.OldValue/Attributes->GetMaxHealth();

	PlayerHUD->GetGauge(EGaugeType::HP)->UpdateWidget(NewHealthPercent,OldHealthPercent);
}

/**
 * 어트리뷰트의 변경에 대한 호출 함수 입니다.
 * @param Data : 변경된 속성의 값이 들어옵니다.
 */
void APlayerStateBase::MaxHealthChange(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("MaxHealthChange"));
}

/**
 * 어트리뷰트의 변경에 대한 호출 함수 입니다.
 * @param Data : 변경된 속성의 값이 들어옵니다.
 */
void APlayerStateBase::StaminaChange(const FOnAttributeChangeData& Data)
{
	const float NewStaminaPercent =Data.NewValue/Attributes->GetMaxMana();
	const float OldStaminaPercent =Data.OldValue/Attributes->GetMaxMana();
	PlayerHUD->GetGauge(EGaugeType::Stamina)->UpdateWidget(NewStaminaPercent,OldStaminaPercent);
}

/**
 * 어트리뷰트의 변경에 대한 호출 함수 입니다.
 * @param Data : 변경된 속성의 값이 들어옵니다.
 */
void APlayerStateBase::MaxManaChange(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("MaxManaChange"));
}


