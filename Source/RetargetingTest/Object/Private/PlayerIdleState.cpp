// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PlayerIdleState.h"

#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"

UPlayerIdleState::UPlayerIdleState()
{
	StateGameplayTag.FromExportString("State.Idle");

}

bool UPlayerIdleState::CanPerformState()
{
	//Idle 스테이트를 위한 진입조건을 설정합니다.
	//떨어지는 상태가 아니고, 속도가 0일때.
	if(PerformingActor->GetVelocity()==FVector::ZeroVector)
		return true;
	return Super::CanPerformState();
}
