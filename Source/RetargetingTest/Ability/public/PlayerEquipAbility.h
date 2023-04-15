// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerAbility.h"
#include "UObject/Object.h"
#include "PlayerEquipAbility.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UPlayerEquipAbility : public UBasePlayerAbility
{
	GENERATED_BODY()

public:
	UPlayerEquipAbility();
public:
	virtual void StartAbility() override;

	virtual bool CanPerformAbility() override;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Montage")
	UAnimMontage* EquipMontage;
};
