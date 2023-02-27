// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStateObject.h"
#include "PlayerWalkingState.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UPlayerWalkingState : public UBaseStateObject
{
	GENERATED_BODY()



public:
	virtual bool CanPerformState() override;
};
