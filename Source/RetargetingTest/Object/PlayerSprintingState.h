// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerState.h"
#include "PlayerSprintingState.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UPlayerSprintingState : public UBasePlayerState
{
	GENERATED_BODY()
public:
	UPlayerSprintingState();

	virtual bool CanPerformState() override;
};
