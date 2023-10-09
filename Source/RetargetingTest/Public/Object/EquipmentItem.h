// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "EquipmentItem.generated.h"

UENUM()
enum class EEquipment_Type : uint8
{
	Head	=0,
	Armor	=1,
	Pants	=2,
	Weapon	=3,
};


USTRUCT(BlueprintType)
struct FEquipmetStat
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float ATK;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float DEF;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float HP;
};
/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API AEquipmentItem : public AItemBase
{
	GENERATED_BODY()

public:
	AEquipmentItem();
	
	//setter
	void SetEquipItemType(EEquipment_Type NewType);

	//getter
	EEquipment_Type GetEquipItemType() const;
protected:
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,meta=(AllowPrivateAccess=true))
	EEquipment_Type EquipItemType;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,meta=(AllowPrivateAccess=true),Category=Stats)
	FEquipmetStat Stats;
};
