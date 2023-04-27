// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DemoPlayerState.h"

#include "Ability/CharacterAbilitySystemComponent.h"
#include "Attribute/CharacterAttributeSetBase.h"

ADemoPlayerState::ADemoPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	//멀티게임의 경우 리플리케이트모드를 설정함.
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>(TEXT("AttributeSetBase"));

	NetUpdateFrequency=100.0f;
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent* ADemoPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCharacterAttributeSetBase* ADemoPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool ADemoPlayerState::IsAlive() const
{
	return GetHealth()>0.0f;
}

void ADemoPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	//TODO - implement HUD later
	
}


float ADemoPlayerState::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float ADemoPlayerState::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

float ADemoPlayerState::GetMana() const
{
	return AttributeSetBase->GetMana();
}

float ADemoPlayerState::GetMaxMana() const
{
	return AttributeSetBase->GetMaxMana();
}

int32 ADemoPlayerState::GetCharacterLevel() const
{
	return AttributeSetBase->GetLevel();
}

void ADemoPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if(AbilitySystemComponent)
	{
		HealthChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this,&ADemoPlayerState::HealthChange);
		MaxHealthChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this,&ADemoPlayerState::MaxHealthChange);
		ManaChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetManaAttribute()).AddUObject(this,&ADemoPlayerState::ManaChange);
		MaxManaChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxManaAttribute()).AddUObject(this,&ADemoPlayerState::MaxManaChange);
		CharacterLevelChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetLevelAttribute()).AddUObject(this,&ADemoPlayerState::CharacterLevelChange);

		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")),EGameplayTagEventType::NewOrRemoved).AddUObject(this,&ADemoPlayerState::StunTagChanged);
	}
}

void ADemoPlayerState::HealthChange(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("Health Change"));
}

void ADemoPlayerState::MaxHealthChange(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("MaxHealth Change"));
}

void ADemoPlayerState::ManaChange(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("Mana Change"));
}

void ADemoPlayerState::MaxManaChange(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("MaxMana Change"));
}

void ADemoPlayerState::CharacterLevelChange(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("CharacterLevel Change"));
}

void ADemoPlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if(NewCount>0)
	{
		FGameplayTagContainer AbilityTagToCancel;
		AbilityTagToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));

		AbilitySystemComponent->CancelAbilities(&AbilityTagToCancel,&AbilityTagsToIgnore);
	}
}
