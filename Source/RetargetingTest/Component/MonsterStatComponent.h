// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterStatComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UMonsterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMonsterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void GetDamaged(const float& Damage);
	void SetHP(const float& NewHP);
	float GetHPRatio() const;
	float GetAttackDamage(); //getter

public:
	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;
	
private:
	const float MaxHP=200.0f;

	UPROPERTY()
	float CurrentHP;

	float AttackDamage=10.0f;

};
