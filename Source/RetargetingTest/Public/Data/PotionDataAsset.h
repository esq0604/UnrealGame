// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolDataAsset.h"
#include "PotionDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UPotionDataAsset : public UToolDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,Category="Potion Data")
	float RecoveryValue; 
};
