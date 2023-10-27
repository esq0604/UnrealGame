// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slot.h"
#include "UObject/Object.h"
#include "EquipmentSlot.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UEquipmentSlot : public USlot
{
	GENERATED_BODY()

public:
	void Renew();
	void SetEquipItemType();
	void GetEquipItemType() const;
private:
	//장비의 경우 슬롯의 넘버와 인덱스를 Enum타입으로 지정해줍니다.
	// UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,meta=(AllowPrivateAccess=true))
	// EEquipment_Type EquipItemType;
};
