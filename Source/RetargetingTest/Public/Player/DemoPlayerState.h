// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Attribute/CharacterAttributeSetBase.h"
#include "GameFramework/PlayerState.h"
#include "DemoPlayerState.generated.h"

class UCharacterAbilitySystemComponent;
class UPlayerHUD;
/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API ADemoPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ADemoPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UCharacterAttributeSetBase* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category="DempPlayerState")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable,Category="DemoPlayerState")
	void ShowAbilityConfirmCancelText(bool ShowText);

	UFUNCTION(BlueprintCallable,Category="Attributes")
	float GetHealth() const;
	
	UFUNCTION(BlueprintCallable,Category="Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable,Category="Attributes")
	float GetMana() const;

	UFUNCTION(BlueprintCallable,Category="Attributes")
	float GetMaxMana() const;
	
	UFUNCTION(BlueprintCallable,Category="Attributes")
	int32 GetCharacterLevel() const;

protected:
	virtual void BeginPlay() override;
	
	virtual void HealthChange(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChange(const FOnAttributeChangeData& Data);
	virtual void ManaChange(const FOnAttributeChangeData& Data);
	virtual void MaxManaChange(const FOnAttributeChangeData& Data);
	virtual void CharacterLevelChange(const FOnAttributeChangeData& Data);

	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
protected:
	UPROPERTY()
	UCharacterAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UCharacterAttributeSetBase* AttributeSetBase;

	FGameplayTag DeadTag;

	FDelegateHandle HealthChangeDelegateHandle;
	FDelegateHandle MaxHealthChangeDelegateHandle;
	FDelegateHandle ManaChangeDelegateHandle;
	FDelegateHandle MaxManaChangeDelegateHandle;
	FDelegateHandle CharacterLevelChangeDelegateHandle;
};
