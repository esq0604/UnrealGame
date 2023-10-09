// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EquipmentSlot.h"

void UEquipmentSlot::Renew()
{
	
}

void UEquipmentSlot::SetEquipItemType(EEquipment_Type Type)
{
	EquipItemType=Type;
}

EEquipment_Type UEquipmentSlot::GetEquipItemType() const
{
	return EquipItemType;
}
