// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerState.h"
#include "PlayerIdleState.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UPlayerIdleState : public UBasePlayerState
{
	GENERATED_BODY()
public:
	UPlayerIdleState();

	virtual bool CanPerformState() override;
};
