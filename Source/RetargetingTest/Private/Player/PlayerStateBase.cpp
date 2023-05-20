// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerStateBase.h"

#include "AbilitySystemComponent.h"
#include "Attribute/RuneAttributeSet.h"

// Sets default values
APlayerStateBase::APlayerStateBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<URuneAttributeSet>(TEXT("Attribute"));
}

UAbilitySystemComponent* APlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

URuneAttributeSet* APlayerStateBase::GetAttributes() const
{
	return Attributes;
}

// Called when the game starts or when spawned
void APlayerStateBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

