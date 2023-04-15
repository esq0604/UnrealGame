// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RetargetingTest/State/Public/BaseStateObject.h"
#include "PDAWeapon.generated.h"

class UBaseAbilityObject;
class UBaseStateObject;
class UAnimMontage;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAbilityMontage
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Abilities")
	TSubclassOf<UBaseAbilityObject> Ability;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Montage")
	TArray<UAnimMontage*> ListOfMontage;
};

UCLASS()
class RETARGETINGTEST_API UPDAWeapon : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="States")
	TArray<TSubclassOf<UBaseStateObject>>  StatesToCreate;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Abilities")
	TArray<FAbilityMontage> Abilities;
};
