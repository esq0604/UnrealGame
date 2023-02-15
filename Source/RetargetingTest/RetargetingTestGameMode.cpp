// Copyright Epic Games, Inc. All Rights Reserved.

#include "RetargetingTestGameMode.h"
#include "Player/RetargetingTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARetargetingTestGameMode::ARetargetingTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
