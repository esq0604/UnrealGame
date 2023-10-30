#pragma once

#include "CoreMinimal.h"
#include "EquipmentDataAsset.h"
#include "Data/ItemDataAsset.h"
#include "WeaponDataAsset.generated.h"

class UCustomAbilitySet;

UENUM()
enum class EWeaponType
{
	RightWeapon		UMETA(DisplayName="RightWeapon"),
	LeftWeapon		UMETA(DisplayName="LeftWeapon"),
	TwoHandWeapon	UMETA(DisplayName="TwoHandWeapon"),
};

USTRUCT()
struct FWeaponStatistics
{
	GENERATED_BODY()

	FWeaponStatistics() : Damage(0)
	{
	}
	UPROPERTY(EditAnywhere)
	float Damage;

	//추가할 속성이 있다면 추가합니다.
};

USTRUCT()
struct FWeaponTraceSocketName
{
	GENERATED_BODY()

	FWeaponTraceSocketName() :
		TraceStartSocketName(""),
		TraceEndSocketName("")
	{
	}
	
	UPROPERTY(EditAnywhere)
	FName TraceStartSocketName;
	UPROPERTY(EditAnywhere)
	FName TraceEndSocketName;
};

UCLASS()
class UWeaponDataAsset : public UEquipmentDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,Category="Weapon Data")
	EWeaponType WeaponType;
	UPROPERTY(EditAnywhere,Category="Weapon Data")
	FWeaponStatistics WeaponStatistics;
	UPROPERTY(EditAnywhere,Category="Weapon Data")
	FWeaponTraceSocketName WeaponSocketName;
	UPROPERTY(EditAnywhere,Category="Weapon Data")
	TArray<TObjectPtr<UCustomAbilitySet>> WeaponAbilitySet;
};
