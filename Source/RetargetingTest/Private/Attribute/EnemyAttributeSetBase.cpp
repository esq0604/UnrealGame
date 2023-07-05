// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/EnemyAttributeSetBase.h"

#include "Net/UnrealNetwork.h"

void UEnemyAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnemyAttributeSetBase, Health, OldHealth);
}

void UEnemyAttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnemyAttributeSetBase, MaxHealth, OldMaxHealth);

}

void UEnemyAttributeSetBase::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnemyAttributeSetBase, MaxHealth, OldArmor);

}

void UEnemyAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UEnemyAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEnemyAttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);
}
