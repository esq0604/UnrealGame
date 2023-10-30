// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataAsset.h"
#include "UObject/Object.h"
#include "EquipmentDataAsset.generated.h"

/**
 * 
 */

class UCustomAbilitySet;
class UCustomGameplayAbility;
USTRUCT()
struct FMyStruct
{
	GENERATED_BODY()
	
};

UCLASS()
class RETARGETINGTEST_API UEquipmentDataAsset : public UItemDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Durability;
	UPROPERTY(EditAnywhere)
	FName AttachSocketName;
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<const UCustomAbilitySet>> AbilitySetToEquip;
};
