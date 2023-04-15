// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerAbility.h"
#include "UObject/Object.h"
#include "PlayerLightAttackAbility.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UPlayerLightAttackAbility : public UBasePlayerAbility
{
	GENERATED_BODY()
public:
	UPlayerLightAttackAbility();
	
	virtual void StartAbility() override;

	virtual bool CanPerformAbility() override;

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Light Attack Ability")
	TArray<UAnimMontage*> AnimMontages;
	
	int32 ComboAttackIndex=0;
};
