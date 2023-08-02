// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GameplayAbility_MeleeWeapon.h"

UGameplayAbility_MeleeWeapon::UGameplayAbility_MeleeWeapon(const FObjectInitializer& ObjectInitializer)
{
}

ABaseWeaponInstance* UGameplayAbility_MeleeWeapon::GetWeaponInstance()
{
	return nullptr;
}

FHitResult UGameplayAbility_MeleeWeapon::WeaponTrace(const FVector& StartTrace, const FVector& EndTrace,
	float SweapRadius, bool bIsSimulated, TArray<FHitResult>& OutHitResults) const
{
	return FHitResult();
}
