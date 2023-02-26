// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterStatComponent.h"


// Sets default values for this component's properties
UMonsterStatComponent::UMonsterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent=true;

}

void UMonsterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetHP(MaxHP);
}

// Called when the game starts
void UMonsterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMonsterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//데미지를 입었을때 입니다.
void UMonsterStatComponent::GetDamaged(const float& Damage)
{
	SetHP(FMath::Clamp<float>(CurrentHP-Damage,0.0f,MaxHP));
}


void UMonsterStatComponent::SetHP(const float& NewHP)
{
	CurrentHP=NewHP;
	OnHPChanged.Broadcast();
	if(CurrentHP<KINDA_SMALL_NUMBER)
	{
		CurrentHP =0.0f;
		OnHPIsZero.Broadcast();
	}
}

float UMonsterStatComponent::GetHPRatio() const
{
	return (MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / MaxHP); 
}

float UMonsterStatComponent::GetAttackDamage()
{
	return AttackDamage;
}
