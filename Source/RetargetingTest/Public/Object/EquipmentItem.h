// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Data/EquipmentDataAsset.h"
#include "EquipmentItem.generated.h"


class UEquipmentDataAsset;
/**
 * 
 */
class UStaticMeshComponent;
UCLASS()
class RETARGETINGTEST_API AEquipmentItem : public AItemBase
{
	GENERATED_BODY()

public:
	AEquipmentItem();
	
	//setter
	void SetEquipItemType();
	//getter
	void GetEquipItemType() const;
	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent() const { return StaticMeshComponent;}
	FORCEINLINE UStaticMesh* GetMesh() const {return StaticMeshComponent->GetStaticMesh();}
	//function
	void Init();
	virtual void Equip(ACharacter* Character,UItemDataAsset* InItemData);
	virtual void UnEquip(ACharacter* Character);
protected:

private:
	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess=true) ,Category = "Equipment|")
	TWeakObjectPtr<ACharacterBase> OwningCharacter;

};
