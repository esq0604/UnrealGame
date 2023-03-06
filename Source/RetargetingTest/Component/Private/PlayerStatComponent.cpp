// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/PlayerStatComponent.h"


// Sets default values for this component's properties
UPlayerStatComponent::UPlayerStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

float UPlayerStatComponent::GetAttackDamage()
{
	return AttackDamage;
}

// Called when the game starts
void UPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/**
 * 체력을 조정합니다. 피가 0이 된다면 델리게이트를 호출합니다.
 * @param NewHP - 변경될 체력이 들어옵니다.
 */
void UPlayerStatComponent::SetHP(const float& NewHP)
{
	CurrentHpPercent=GetHPRatio(CurrentHP); //현재 피 퍼센트
	NewHpPercent=GetHPRatio(NewHP); //받아서 까인 피 퍼센트
	OnHPChanged.Broadcast(); //widget 처리 후
	CurrentHP=NewHP; //현재 피 갱신 
	if(CurrentHP<KINDA_SMALL_NUMBER)
	{
		CurrentHP =0.0f;
		OnHPIsZero.Broadcast();
	}
} 
/**
 * 프로그레스바에 체력의 퍼센트를 전달하기 위해 전체체력에 대한 현제 체력 퍼센트를 계산합니다.
 */
float UPlayerStatComponent::GetHPRatio(const float& ChangedHP)
{
	return (MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (ChangedHP / MaxHP); 
}

/**
 * 플레이어가 데미지를 받았을시 실행됩니다. 체력을 조정하도록 합니다.
 * @param Damage - 받은 데미지의 양이 들어옵니다.
 */
void UPlayerStatComponent::GetDamaged(const float& Damage)
{
	UE_LOG(LogTemp,Warning,TEXT("CurrentHP-Damage %f"),FMath::Clamp<float>(CurrentHP-Damage,0.0f,MaxHP));
	SetHP(FMath::Clamp<float>(CurrentHP-Damage,0.0f,MaxHP));
}


