// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "RetargetingTest/RetargetingTest.h"
#include "AbilitySystemTestCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, AAbilitySystemTestCharacter*, character);

UCLASS()
class RETARGETINGTEST_API AAbilitySystemTestCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAbilitySystemTestCharacter(const class FObjectInitializer& ObjectInitializer);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void AddCharacterAbilities();

	virtual void InitilizeAttributes();

	virtual void AddStartupEffects();

	virtual void SetHealth(float Health);

	virtual void SetMana(float Mana);
public:
	UPROPERTY(BlueprintCallable, Category="Character")
	FCharacterDiedDelegate OnCharacterDied;

	UFUNCTION(BlueprintCallable, Category="Character")
	virtual bool IsAlive() const;
	
	UFUNCTION(BlueprintCallable, Category="Character")
	virtual int32 GetAbilityLevel(AbilityID AbilityID) const;

	virtual void RemoveCharacterAbilities();

	virtual void Die();

	UFUNCTION(BlueprintCallable,Category="Character") 
	virtual void FinishDying();

	UFUNCTION(BlueprintCallable, Category="Character|Attributes")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category="Character|Attributes")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category="Character|Attributes")
	float GetMana() const;
	UFUNCTION(BlueprintCallable, Category="Character|Attributes")
	float GetMaxMana() const;
	
protected:
	TWeakObjectPtr<class UCharacterAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UCharacterAttributeSetBase> AttributeSetBase;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Character")
	FText CharacterName;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Character|Animation")
	UAnimMontage* DeathMontage;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Character|Abilities")
	TArray<TSubclassOf<class UCharacterGameplayAbility>> CharacterAbilities;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Character|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Character|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;
	
};
