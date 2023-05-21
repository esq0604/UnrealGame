// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerStateBase.h"

#include "AbilitySystemComponent.h"
#include "Attribute/RuneAttributeSet.h"
#include "Controller/MyPlayerController.h"
#include "UI/PlayerGauge.h"
#include "UI/PlayerHUD.h"

// Sets default values
APlayerStateBase::APlayerStateBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<URuneAttributeSet>(TEXT("Attribute"));
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

URuneAttributeSet* APlayerStateBase::GetAttributes() const
{
	return Attributes;
}

void APlayerStateBase::SetPlayerHUD(UPlayerHUD* NewPlayerHUD)
{
	PSPlayerHUD=NewPlayerHUD;
	
	//PlayerHUD->Child
}

// Called when the game starts or when spawned
void APlayerStateBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("PCPlayerState BeginPlay"));
	//const AMyPlayerController*  PC= Cast<AMyPlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
	
	if(AbilitySystemComponent)
	{
		HealthChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute()).AddUObject(this,&APlayerStateBase::HealthChange);
		MaxHealthChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxHealthAttribute()).AddUObject(this,&APlayerStateBase::MaxHealthChange);
		StaminaChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetStaminaAttribute()).AddUObject(this,&APlayerStateBase::StaminaChange);
		MaxManaChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxManaAttribute()).AddUObject(this,&APlayerStateBase::MaxManaChange);
	}
	
}

/**
 * 어트리뷰트의 변경에 대한 호출 함수 입니다.
 * @param Data : 변경된 속성의 값이 들어옵니다.
 */
void APlayerStateBase::HealthChange(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("HealthChange"));
	const float NewHealthPercent=(Data.NewValue/Attributes->GetMaxHealth());
	PSPlayerHUD->GetGauge()->UpdateHPWidget(NewHealthPercent);
}

/**
 * 어트리뷰트의 변경에 대한 호출 함수 입니다.
 * @param Data : 변경된 속성의 값이 들어옵니다.
 */
void APlayerStateBase::MaxHealthChange(const FOnAttributeChangeData& Data)
{
}

/**
 * 어트리뷰트의 변경에 대한 호출 함수 입니다.
 * @param Data : 변경된 속성의 값이 들어옵니다.
 */
void APlayerStateBase::StaminaChange(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("StamChange"));
	const float NewStaminaPercent=(Data.NewValue/Attributes->GetMaxStamina());
	PSPlayerHUD->GetGauge()->UpdateStaminaWidget(NewStaminaPercent);
}

/**
 * 어트리뷰트의 변경에 대한 호출 함수 입니다.
 * @param Data : 변경된 속성의 값이 들어옵니다.
 */
void APlayerStateBase::MaxManaChange(const FOnAttributeChangeData& Data)
{
}


