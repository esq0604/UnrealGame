// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroSignature);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UBaseStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseStatComponent();

	virtual void SetHP(const float& NewHp);

	virtual float GetHPRatio(const float& ChangedHP);

	virtual void SufferDamage(const float& Damage);
	
	virtual float GetAttackDamage() const;
	
	float GetCurrentHpPercent() const ;
	
	UFUNCTION(BlueprintCallable)
	float GetNewHpPercent() const;
public:
	FOnHPIsZeroSignature OnHPIsZeroDelegate;
	FOnHPChangedSignature OnHPChangedDelegate;
	
protected:
	float CurrentHp;
	float MaxHp;
	float CurrentHpPercent;
	float NewHpPercent;
	float AttackDamage;

private:

};
