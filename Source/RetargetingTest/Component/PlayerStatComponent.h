// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UPlayerStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerStatComponent();

	float GetAttackDamage();

	void GetDamaged(const float& Damage);
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	void SetHP(const float& NewHP);
	
	float GetHPRatio();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;
private:
	float AttackDamage=50.0f;

	float MaxHP=100.0f;
	float CurrentHP=MaxHP;
};
