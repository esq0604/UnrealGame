// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterStatComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroSignature);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UMonsterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMonsterStatComponent();
	
	float GetCurrentHpPercent() const;
	float GetReducedHpPercent() const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/*Stter*/
	void SetHP(const float& NewHP);

	/*Getter*/
	void GetDamaged(const float& Damage);
	float GetHPRatio(const float& HP) const;
	float GetAttackDamage() const; 

public:
	FOnHPIsZeroSignature OnHPIsZeroDelegate;
	FOnHPChangedSignature OnHPChangedDelegate;
private:
	const float MaxHP=200.0f;

	UPROPERTY()
	float CurrentHp=MaxHP;
	float ReducedHp;
	float CurrentHpPercent;
	float ReducedHpPercent;
	float AttackDamage=10.0f;

};
