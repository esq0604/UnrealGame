// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RetargetingTest/Object/Public/BaseStateObject.h"
#include "PDAWeapon.generated.h"


class UPlayerEquipState;
class UBaseStateObject;
/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UPDAWeapon : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="States")
	TArray<UBaseStateObject*>  StatesToCreate;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="States")
	UPlayerEquipState* EquipState;
};
