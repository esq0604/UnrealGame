// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStateManagerComponent.h"

#include "RetargetingTest/Object/BaseStateObject.h"
#include "RetargetingTest/Object/PlayerDodgeState.h"
#include "RetargetingTest/Object/PlayerIdleState.h"
#include "RetargetingTest/Object/PlayerJumpingState.h"
#include "RetargetingTest/Object/PlayerSprintingState.h"
#include "RetargetingTest/Object/PlayerWalkingState.h"


// Sets default values for this component's properties
UBaseStateManagerComponent::UBaseStateManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//DodgeStateTest=;
	//WalkingStateTest=;
	ActivatableStates.Add(CreateDefaultSubobject<UPlayerDodgeState>(TEXT("DodgeState")));
	ActivatableStates.Add(CreateDefaultSubobject<UPlayerWalkingState>(TEXT("WalkingState")));
	ActivatableStates.Add(CreateDefaultSubobject<UPlayerIdleState>(TEXT("IdleState")));
	ActivatableStates.Add(CreateDefaultSubobject<UPlayerJumpingState>(TEXT("JumpState")));
	ActivatableStates.Add(CreateDefaultSubobject<UPlayerSprintingState>(TEXT("SprintState")));

	//ActivatableStates.AddUnique(CreateDefaultSubobject<UPlayerIdleState>(TEXT("IdleState")));
	//ActivatableStates.AddUnique(CreateDefaultSubobject<UPlayerJumpingState>(TEXT("JumpingState")));

	//CurrentActiveState=ActivatableStates[0];
}


// Called when the game starts
void UBaseStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UBaseStateManagerComponent::PerformStateOfClass(TSubclassOf<UBaseStateObject> StateToSet)
{
}

void UBaseStateManagerComponent::SetPerformingActor(AActor* SettedActor)
{
	PerformingActor=SettedActor;
}


void UBaseStateManagerComponent::SetCurrentActiveState(UBaseStateObject* NewCurrentActiveState)
{
	//if(NewCurrentActiveState->CanPerformState())
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

void UBaseStateManagerComponent::ConstructStatebyClass(TSubclassOf<UBaseStateObject> StateToConstruct)
{
	//ConstructedState=nullptr;

	if(StateToConstruct)
	{
		UBaseStateObject* LocalNewState;
		LocalNewState = NewObject<UBaseStateObject>(PerformingActor,StateToConstruct);

		ActivatableStates.AddUnique(LocalNewState);
		LocalNewState->SetPerformingActor(PerformingActor);
		UE_LOG(LogTemp,Warning,TEXT("ActivatableStates %d"),ActivatableStates.Num());
	}
}

//get state by gameplayTag
UBaseStateObject* UBaseStateManagerComponent::GetStateOfGameplayTag(FGameplayTag StateGamePlayTag)
{
	 
	for(int32 i=0; i<ActivatableStates.Num(); i++)
	{
		if(ActivatableStates[i])
		{
			if(ActivatableStates[i]->StateGameplayTag==StateGamePlayTag)
			{
				return ActivatableStates[i];
				
			}
		}
	}
	return nullptr;
}  

