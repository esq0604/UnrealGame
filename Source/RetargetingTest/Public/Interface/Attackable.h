// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Attackable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAttackable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RETARGETINGTEST_API IAttackable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void ToggleWeaponCollision(bool bIsEnable);
	virtual void ToggleWeaponCollision_Implementation(bool bIsEnable) =0;
};
