// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerIdleState.h"

UPlayerIdleState::UPlayerIdleState()
{
	StateGameplayTag.FromExportString("State.Idle");

}

bool UPlayerIdleState::CanPerformState()
{
	//Idle 스테이트를 위한 진입조건을 설정합니다.
	
	return Super::CanPerformState();
}
