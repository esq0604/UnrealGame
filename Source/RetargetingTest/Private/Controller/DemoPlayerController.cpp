// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DemoPlayerController.h"

#include "Player/DemoPlayerState.h"

void ADemoPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ADemoPlayerState* PS = GetPlayerState<ADemoPlayerState>();
	if(PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerState,InPawn);
	}
}

//TODO - Add HUD stuff
