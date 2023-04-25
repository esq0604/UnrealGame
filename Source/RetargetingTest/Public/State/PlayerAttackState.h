// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerState.h"
#include "PlayerAttackState.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UPlayerAttackState : public UBasePlayerState
{
	GENERATED_BODY()
public:
	UPlayerAttackState();

	virtual bool CanPerformState() override;

	virtual void StartState() override;

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Abilites")
	TArray<TSubclassOf<UBaseAbilityObject>> AttackAbilites;
};
