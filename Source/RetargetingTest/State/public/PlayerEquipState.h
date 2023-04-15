// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerState.h"
#include "UObject/Object.h"
#include "PlayerEquipState.generated.h"

class UBaseAbilityObject;
/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UPlayerEquipState : public UBasePlayerState
{
	GENERATED_BODY()

public:
	UPlayerEquipState();

	virtual void StartState() override;
	virtual bool CanPerformState() override;
	virtual void EndState() override;
	bool IsEquipWeapon= false;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability")
	TSubclassOf<UBaseAbilityObject> EquipAbility;

};
