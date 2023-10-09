// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputDataAsset.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Player Inputs")
	TArray<UInputAction*> Inputs;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputMove;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputAttack;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputSprint;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputLook;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputJump;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputToggleInventory;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputInteract;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputAssanation;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputBlock;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputUseQuickSlot_One;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputUseQuickSlot_Two;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputUseQuickSlot_Three;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputUseQuickSlot_Four;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputEquipUnEquip;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputRoll;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputTargetLook;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputParry;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputToggleEquipment;
};
