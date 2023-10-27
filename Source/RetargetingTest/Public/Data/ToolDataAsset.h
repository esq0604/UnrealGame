// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataAsset.h"
#include "ToolDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UToolDataAsset : public UItemDataAsset
{
	GENERATED_BODY()

	UPROPERTY()
	float ToolValue;
};
