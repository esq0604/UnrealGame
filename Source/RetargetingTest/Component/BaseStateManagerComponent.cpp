// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStateManagerComponent.h"


// Sets default values for this component's properties
UBaseStateManagerComponent::UBaseStateManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
}


// Called when the game starts
void UBaseStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UBaseStateManagerComponent::PerformStateOfClass(TSubclassOf<UBaseStateObject> StateToSet)
{
}


void UBaseStateManagerComponent::SetCurrentActiveState(UBaseStateObject* NewCurrentActiveState)
{
	CurrentActiveState = NewCurrentActiveState;
	
}


void UBaseStateManagerComponent::GetStateOfClass(TSubclassOf<UBaseStateObject> StateToSearch,
	UBaseStateObject*& FoundState)
{
	for(int32 i =0; i<ActivatableStates.Num(); i++)
	{
		if(ActivatableStates[i])
		{
			if(ActivatableStates[i]->GetClass()==StateToSearch)
			{
				FoundState=ActivatableStates[i];
				return;
			}
		}
	}
	FoundState=nullptr;
	return;
}

void UBaseStateManagerComponent::ConstructStateOfClass(TSubclassOf<UBaseStateObject> StateToConstruct,
	UBaseStateObject*& ConstructedState)
{
	ConstructedState=nullptr;

	if(StateToConstruct)
	{
		UBaseStateObject* LocalNewState;
		LocalNewState = NewObject<UBaseStateObject>(GetOwner(),StateToConstruct);

		ActivatableStates.AddUnique(LocalNewState);
		LocalNewState->SetPerformingActor(PerformingActor);
		LocalNewState->ConstructState();
		ConstructedState = LocalNewState;
	}
}  

