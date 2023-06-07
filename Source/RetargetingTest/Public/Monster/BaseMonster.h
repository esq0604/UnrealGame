// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseMonster.generated.h"

class UWidgetComponent;
class UEnemyAttributeSetBase;
DECLARE_DELEGATE_OneParam(FMonsterDieSignature, ABaseMonster*)

class UProgressBar;
class USkeletalMeshComponent;
class UBaseMonsterAnimInstance;
class UGameplayEffect;
class UGameplayAbility;
class UEnemyAttributeSetBase;
class UMonsterGauge;

struct FOnAttributeChangeData;
struct FDamageEvent;
UCLASS()
class RETARGETINGTEST_API ABaseMonster : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMonster();
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void InitializeAttributes();
	virtual void GiveDefaultAbilities();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

private:
	virtual void HealthChange(const FOnAttributeChangeData& Data);


public:
	FMonsterDieSignature MonsterDieDelegate;

protected:
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="EnemyBase | Attributes")
	TArray<TSubclassOf<UGameplayEffect>> DefaultAttributeEffects;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="EnemyBase | Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Attributes")
	TObjectPtr<UEnemyAttributeSetBase> Attributes;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Component")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Component")
	TObjectPtr<UWidgetComponent> HPWidgetComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | HPWidget")
	TObjectPtr<UMonsterGauge> HPBarWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | HPWidget")
	TSubclassOf<UMonsterGauge> HPBarWidgetClass;
	
	FDelegateHandle HealthChangeDelegateHandle;
	FDelegateHandle MaxHealthChangeDelegateHandle;
private:
	TObjectPtr<UBaseMonsterAnimInstance> AnimInstacne;
};
