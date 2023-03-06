// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerState.h"
#include "PlayerDodgeState.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UPlayerDodgeState : public UBasePlayerState
{
	GENERATED_BODY()
public:
	UPlayerDodgeState();

	virtual bool CanPerformState() override;
};
