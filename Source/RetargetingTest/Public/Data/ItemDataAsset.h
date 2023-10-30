#pragma once

#include "CoreMinimal.h"
#include "Interface/Useable.h"
#include "ItemDataAsset.generated.h"

class AItemBase;
class UGameplayAbility;
/**
 * 
 */
UENUM()
enum class EItemType : uint8
{
	Tool			UMETA(DisplayName="Tool"),
	Magic			UMETA(DisplayName="Magic"),
	Weapon			UMETA(DisplayName="Weapon"),
	Armor			UMETA(DisplayName="Armor"),
	Quest			UMETA(DisplayName="Quest"),
};

USTRUCT()
struct FItemTextData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FText Name;
	
	UPROPERTY(EditAnywhere)
	FText Description;
	
	UPROPERTY(EditAnywhere)
	FText InteractionText;
	
	UPROPERTY(EditAnywhere)
	FText UsingText;
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

};

USTRUCT()
struct FItemStatistics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float SellValue;
};

USTRUCT()
struct FItemNumericData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	int32 Quantity;

	UPROPERTY(EditAnywhere)
	float Weight;
	
	UPROPERTY(EditAnywhere)
	int32 MaxStackSize;
	
	UPROPERTY(EditAnywhere)
	bool IsStackable;
};

UCLASS()
class UItemDataAsset : public UPrimaryDataAsset 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,Category="Item Data")
	FText ID;
	UPROPERTY(EditAnywhere,Category="Item Data")
	FItemTextData TextData;
	UPROPERTY(EditAnywhere,Category="Item Data")
	FItemAssetData AssetData;
	UPROPERTY(EditAnywhere,Category="Item Data")
	FItemNumericData NumericData;
	UPROPERTY(EditAnywhere,Category="Item Data")
	EItemType ItemType;
	UPROPERTY(EditAnywhere,Category="Item Data")
	TSubclassOf<AItemBase> ActorToSpawn;

};

