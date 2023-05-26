// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EHitReaction.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EHitReaction : uint8
{
	Backward = 0 UMETA(DisplayName="Backward"),
	Forward = 1 UMETA(DisplayName="Forward")
};
