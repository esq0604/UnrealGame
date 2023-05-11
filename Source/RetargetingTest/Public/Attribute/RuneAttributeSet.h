// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RuneAttributeSet.generated.h"

//ATTRIBUTE_ACCESSORS
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class RETARGETINGTEST_API URuneAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	URuneAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	
	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);

	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	
	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);
	
	UFUNCTION()
	virtual void OnRep_Vigor(const FGameplayAttributeData& OldVigor);

	UFUNCTION()
	virtual void OnRep_Mind(const FGameplayAttributeData& OldMind);

	UFUNCTION()
	virtual void OnRep_Endurance(const FGameplayAttributeData& OldEndurance);

	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UFUNCTION()
	virtual void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity);

	UFUNCTION()
	virtual void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);

	UFUNCTION()
	virtual void OnRep_Faith(const FGameplayAttributeData& OldFaith);
	
	UFUNCTION()
	virtual void OnRep_Luck(const FGameplayAttributeData& OldLuck);
public:
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(URuneAttributeSet, Health);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(URuneAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(URuneAttributeSet, Mana);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(URuneAttributeSet, MaxMana);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(URuneAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(URuneAttributeSet, MaxStamina);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(URuneAttributeSet, Vigor);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Mind;
	ATTRIBUTE_ACCESSORS(URuneAttributeSet, Mind);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Endurance;
	ATTRIBUTE_ACCESSORS(URuneAttributeSet, Endurance);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(URuneAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(URuneAttributeSet, Dexterity);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(URuneAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Faith;
	ATTRIBUTE_ACCESSORS(URuneAttributeSet, Faith);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Luck;
	ATTRIBUTE_ACCESSORS(URuneAttributeSet, Luck);
};
