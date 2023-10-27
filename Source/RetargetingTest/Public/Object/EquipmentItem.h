// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "EquipmentItem.generated.h"

 
/**
 * 
 */
UCLASS(Abstract)
class RETARGETINGTEST_API AEquipmentItem : public AItemBase
{
	GENERATED_BODY()

public:
	AEquipmentItem();
	
	//setter
	void SetEquipItemType();

	//getter
	void GetEquipItemType() const;
protected:
	
};
