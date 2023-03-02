// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDodgeState.h"

UPlayerDodgeState::UPlayerDodgeState()
{
	StateGameplayTag.FromExportString("State.Dodge");
}

bool UPlayerDodgeState::CanPerformState()
{
	//닷지 스테이트가 활성화 되기 위해서는, 움직이고, 떨어지지 않을때 입니다.
	//공격중에 특정 시간동안 닷지 스테이트가 가능합닌다.
	return Super::CanPerformState();
}
