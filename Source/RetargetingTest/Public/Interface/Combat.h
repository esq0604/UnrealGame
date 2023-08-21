// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Combat.generated.h"

UENUM()
enum class EHitDirection
{
	Forward,
	Backward,
	Left,
	Right
};
// This class does not need to be modified.
UINTERFACE()
class UCombat : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RETARGETINGTEST_API ICombat
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Combat")
	void ToggleWeaponCollision(bool IsEnable);
	virtual void ToggleWeaponCollision_Implementation(bool IsEnable) =0;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Combat")
	UAnimMontage* GetHitReaction(EHitDirection HitDirection);
	virtual UAnimMontage* GetHitReaction_Implementation(EHitDirection HitDirection)=0;
};
