// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class DemoAbilityID : uint8
{
	None UMETA(DisplayName = "None" ),
	Confirm UMETA(DisplayName = "Confirm" ),
	Cancel UMETA(DisplayName = "Cancel" ),
	Ability1 UMETA(DisplayNAme = "Ability1"),
	Ability2 UMETA(DisplayNAme = "Ability2"),
	Ability3 UMETA(DisplayNAme = "Ability3"),
	Ability4 UMETA(DisplayNAme = "Ability4"),
	Ability5 UMETA(DisplayNAme = "Ability5"),
}; 