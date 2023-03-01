// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStateObject.h"
#include "../Component/BaseStateManagerComponent.h"

UBaseStateObject::UBaseStateObject()
{
}

bool UBaseStateObject::CanPerformState()
{
	return true;
}

void UBaseStateObject::ConstructState()
{
}
