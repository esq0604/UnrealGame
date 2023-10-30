// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/PotionDataAsset.h"

#include "Player/CharacterBase.h"

bool UPotionDataAsset::UseItem(ACharacterBase* Character)
{
	if(NumericData.Quantity>0)
	{
		NumericData.Quantity--;
		return true;
	}
	else
	{
		return false;
	}
}
