// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CustomAbilitySet.generated.h"
class UAbilitySystemComponent;
class UGameplayEffect;
class UCustomGameplayAbility;
/**
 * 
 */
USTRUCT()
struct FAbilitySet_GameplayAbility
{
	GENERATED_BODY()
	
	// Gameplay ability to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCustomGameplayAbility> Ability = nullptr;
};


USTRUCT()
struct FAbilitySet_AttributeSet
{
	GENERATED_BODY()

};

USTRUCT()
struct FAbilitySet_GameplayEffect
{
	GENERATED_BODY()
	
	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;
};
UCLASS()
class RETARGETINGTEST_API UCustomAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	void GiveToAbilitySystem(UAbilitySystemComponent* ASC, UObject* SourceObject = nullptr) const;

	// Gameplay abilities to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta=(TitleProperty=Ability))
	TArray<FAbilitySet_GameplayAbility> EquippedGameplayAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects", meta=(TitleProperty=GameplayEffect))
	TArray<FAbilitySet_GameplayEffect> EquippedGameplayEffects;
protected:

};
