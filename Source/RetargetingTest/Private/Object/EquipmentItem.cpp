// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/EquipmentItem.h"

AEquipmentItem::AEquipmentItem()
{
}

void AEquipmentItem::SetEquipItemType(EEquipment_Type NewType)
{
	EquipItemType=NewType;
}

EEquipment_Type AEquipmentItem::GetEquipItemType() const
{
	return EquipItemType;
}
