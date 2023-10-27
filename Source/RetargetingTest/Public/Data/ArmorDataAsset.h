#pragma once

#include "CoreMinimal.h"
#include "EquipmentDataAsset.h"
#include "Data/ItemDataAsset.h"
#include "ArmorDataAsset.generated.h"

UENUM()
enum class EArmorType
{
	Chest	UMETA(DisplayName="Chest"),
	Pants	UMETA(DisplayName="Pants"),
	Shoes	UMETA(DisplayName="Shoes"),
	Head	UMETA(DisplayName="Haed")
};

USTRUCT()
struct FArmorStatistics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float PhysicalDefense;
	UPROPERTY(EditAnywhere)
	float MagicDefense;
};



UCLASS()
class UArmorDataAsset : public UEquipmentDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,Category="Armor Data")
	EArmorType ArmorType;

	UPROPERTY(EditAnywhere,Category="Armor Data")
	FArmorStatistics ArmorStatistics;
};
