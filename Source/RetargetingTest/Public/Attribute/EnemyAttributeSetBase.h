// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "EnemyAttributeSetBase.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class RETARGETINGTEST_API UEnemyAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSetBase, Health)
	
	UPROPERTY(BlueprintReadOnly, Category = "MaxHealth", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSetBase, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSetBase, Armor)
	//Damage is a meta attribute used by the DamageExecution to calculate final damage, which then turns
	//Temporary value that only exists on the server. Not replicated.
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSetBase, Damage)

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& OldArmor);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
