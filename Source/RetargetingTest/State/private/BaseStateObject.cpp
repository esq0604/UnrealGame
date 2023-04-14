// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/State/Public/BaseStateObject.h"

#include "RetargetingTest/Ability/public/BaseAbilityObject.h"
#include "RetargetingTest/Component/Public/BaseAbilityManagerComponent.h"
#include "RetargetingTest/Player/Public/CharacterBase.h"


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

/**
 * 어빌리티가 실행가능한지 체크합니다.
 * @param AbilitiesToCheck 체크하기위한 어빌리티배열이 들어옵니다.
 */
bool UBaseStateObject::CheckAbilitesToRun(TArray<TSubclassOf<UBaseAbilityObject>> AbilitiesToCheck)
{
	ACharacterBase* LocalCharacter = dynamic_cast<ACharacterBase*>(PerformingActor);
	UBaseAbilityManagerComponent* LocalAbilityManagerComponent=LocalCharacter->GetAbilityManagerComponent();

	if(LocalAbilityManagerComponent !=nullptr)
	{
		for(TSubclassOf<UBaseAbilityObject> Ability : AbilitiesToCheck)
		{
			if(Ability==nullptr)
				UE_LOG(LogTemp,Warning,TEXT("Ability nullptr"));
			SelectedAbilityToTrigger=Ability;
			if(LocalAbilityManagerComponent->GetAbilityOfClass(Ability))
			{
				UE_LOG(LogTemp,Warning,TEXT("Check Ability To Run Return True"));
				return true;
			}
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("Check Ability To Run Return False"));
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
