// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/State/BaseStateObject.h"


#include "RetargetingTest/Public/Component/BaseAbilityManagerComponent.h"
#include "RetargetingTest/Public/Component/BaseStateManagerComponent.h"


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
	StateManagerComponent->SetCurrentActiveState(nullptr);
}

/**
 * 어빌리티가 실행가능한지 체크합니다.
 * @param AbilitiesToCheck 체크하기위한 어빌리티배열이 들어옵니다.
 */
bool UBaseStateObject::CheckAbilitesToRun(TArray<TSubclassOf<UBaseAbilityObject>> AbilitiesToCheck)
{
	if(AbilityManagerComponent !=nullptr)
	{
		for(TSubclassOf<UBaseAbilityObject> Ability : AbilitiesToCheck)
		{
			if(AbilityManagerComponent->GetCanPerformAbilityOfClass(Ability))
			{
				SelectedAbilityToTrigger=Ability;
				if(AbilityManagerComponent->GetAbilityOfClass(Ability))
				{
					return true;
				}
				
				return false;
			}
		}
		return false;
	}
	return false;
}

bool UBaseStateObject::GetHasTickState() const
{
	return HasTickState;
}

void UBaseStateObject::SetGameplayTag(const FGameplayTag& GameplayTag)
{
	StateGameplayTag=GameplayTag;
}
