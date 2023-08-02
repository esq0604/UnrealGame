// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetManager.h"

#include "AbilitySystemGlobals.h"
void UCustomAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
