// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerState.h"
#include "BaseStateObject.h"
#include "PlayerWalkingState.generated.h"

/**

 * 
 */
UCLASS()
class RETARGETINGTEST_API UPlayerWalkingState : public UBasePlayerState
{
	GENERATED_BODY()

public:
	UPlayerWalkingState();

public:
	virtual bool CanPerformState() override;

	virtual void EndState() override;

	virtual void StartState() override;

};
