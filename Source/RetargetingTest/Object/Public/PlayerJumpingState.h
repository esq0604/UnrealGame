// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerState.h"
#include "PlayerJumpingState.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UPlayerJumpingState : public UBasePlayerState
{
	GENERATED_BODY()
public:
	UPlayerJumpingState();

	virtual bool CanPerformState() override;
};
