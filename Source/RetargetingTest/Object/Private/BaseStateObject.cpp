// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/BaseStateObject.h"
#include "RetargetingTest/Object/Public/BaseStateObject.h"


UBaseStateObject::UBaseStateObject()
{
}

bool UBaseStateObject::CanPerformState()
{
	return true;
}

void UBaseStateObject::StartState()
{
	
}

void UBaseStateObject::TickState()
{
	
}

void UBaseStateObject::EndState()
{
}

void UBaseStateObject::ConstructState()
{
}

void UBaseStateObject::SetGameplayTag(const FGameplayTag& GameplayTag)
{
	StateGameplayTag=GameplayTag;
}
