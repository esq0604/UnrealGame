// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Component/BaseAbilityManagerComponent.h"

#include "GameplayTagContainer.h"
#include "RetargetingTest/Public/Ability/BaseAbilityObject.h"
#include "RetargetingTest/Public/Controller/MyPlayerController.h"


// Sets default values for this component's properties
UBaseAbilityManagerComponent::UBaseAbilityManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseAbilityManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseAbilityManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UBaseAbilityObject* UBaseAbilityManagerComponent::GetCurrentActiveAbility()
{
	return CurrentActiveAbility;
}

UBaseAbilityObject* UBaseAbilityManagerComponent::GetAbilityOfGameplayTag(FGameplayTag AbilityGameplayTag)
{
	for (int32 i = 0; i < ActivatableAbilities.Num(); i++)
	{
		if (ActivatableAbilities[i])
		{
			if (ActivatableAbilities[i]->AbilityGameplayTag == AbilityGameplayTag)
			{
				return ActivatableAbilities[i];
			}
		}
	}
	return nullptr;
}

UBaseAbilityObject* UBaseAbilityManagerComponent::GetAbilityOfClass(TSubclassOf<UBaseAbilityObject> AbilityToSearch)
{
	for (int32 i = 0; i < ActivatableAbilities.Num(); i++)
	{

		if (ActivatableAbilities[i])
		{
			if (ActivatableAbilities[i]->GetClass() == AbilityToSearch)
			{
				return ActivatableAbilities[i];
			}
		}

	}

	return nullptr;
}

bool UBaseAbilityManagerComponent::GetCanPerformAbilityOfClass(TSubclassOf<UBaseAbilityObject> AbilityToSearch)
{
	
	if (AbilityToSearch)
	{

		UBaseAbilityObject* LocalAbility = GetAbilityOfClass(AbilityToSearch);

		if (LocalAbility)
		{
			return LocalAbility->CanPerformAbility();
		}
		else
		{
			UBaseAbilityObject* LocalNewAbility=ConstructAbilityOfClass(AbilityToSearch);
			return LocalNewAbility->CanPerformAbility();
		}
	}
	return false;
}

UBaseAbilityObject* UBaseAbilityManagerComponent::ConstructAbilityOfClass(TSubclassOf<UBaseAbilityObject> AbilityToConstruct)
{
	if (AbilityToConstruct)
	{
		AMyPlayerController* LocalController=dynamic_cast<AMyPlayerController*>(GetWorld()->GetFirstPlayerController());
		UBaseAbilityObject* LocalNewAbility;
		LocalNewAbility = NewObject<UBaseAbilityObject>(GetOwner(), AbilityToConstruct);
		ActivatableAbilities.AddUnique(LocalNewAbility);
		LocalNewAbility->SetPerformingActor(GetOwner());
		LocalNewAbility->SetAbilityManagerComponent(this);
		LocalNewAbility->SetStateManagerComponent(LocalController->GetStateManagerComponent());
		return LocalNewAbility;
	}

	return nullptr;
}

void UBaseAbilityManagerComponent::PerformAbilityOfClass(TSubclassOf<UBaseAbilityObject> AbilityToSet)
{
	TryPerformAbilityOfClass(AbilityToSet,false);
}

bool UBaseAbilityManagerComponent::TryPerformAbilityOfClass(TSubclassOf<UBaseAbilityObject> AbilityToSet,
	bool ConditionCheck)
{
	if (AbilityToSet)
	{
		UBaseAbilityObject* LocalAbility = nullptr;
		LocalAbility=GetAbilityOfClass(AbilityToSet);

		if (LocalAbility)
		{
			if (ConditionCheck)
			{
				if (LocalAbility->CanPerformAbility())
				{
					LocalAbility->StartAbility();
					return true;
				}
			}
			else
			{
				LocalAbility->StartAbility();
				return true;
			}

			return false;
		}
		
		else
		{
			if (ConditionCheck)
			{
				if (LocalAbility->CanPerformAbility())
				{
					LocalAbility->StartAbility();

					return true;
				}
			}
			else
			{
				LocalAbility->StartAbility();

				return true;
			}
		}
	}
	return false;
}

