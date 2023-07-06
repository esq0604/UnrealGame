// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/EnemyAttributeSetBase.h"

#include "Net/UnrealNetwork.h"

void UEnemyAttributeSetBase::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnemyAttributeSetBase, Armor, OldArmor);

}

void UEnemyAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
