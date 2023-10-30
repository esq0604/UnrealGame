// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/EquipmentItem.h"

#include "Data/EquipmentDataAsset.h"
#include "Data/ItemDataAsset.h"
#include "GameFramework/Character.h"
#include "Player/CharacterBase.h"

AEquipmentItem::AEquipmentItem()
{
}

void AEquipmentItem::SetEquipItemType()
{
	//EquipItemType=NewType;
}

void AEquipmentItem::GetEquipItemType() const
{
	
}

void AEquipmentItem::Init()
{
}

//장착시 어빌리티를 부여합니다.
void AEquipmentItem::Equip(ACharacter* Character,UItemDataAsset* InItemData)
{
	UE_LOG(LogTemp,Warning,TEXT("EquipData GetDefault : %s"),*InItemData->GetName());
	const UEquipmentDataAsset* EquipData =dynamic_cast<UEquipmentDataAsset*>(InItemData);

	StaticMeshComponent->SetVisibility(true);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if(Character)
	{
		//UE_LOG(LogTemp,Warning,TEXT("%s"),*EquipData->AttachSocketName.ToString());
		AttachToComponent(Character->GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,EquipData->AttachSocketName);
	}
	
}

/**
 * @brief 장착을 해제 후 인벤토리로 되돌려놓습니다.
 * @param Character 장착을 해제할 캐릭터가 들어옵니다.
 */
void AEquipmentItem::UnEquip(ACharacter* Character)
{
}
