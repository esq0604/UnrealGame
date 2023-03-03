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

	ActiveAbleStates.Add(CreateDefaultSubobject<UPlayerDodgeState>(TEXT("DodgeeState")));
	ActiveAbleStates.Add(CreateDefaultSubobject<UPlayerIdleState>(TEXT("IdleState")));
	ActiveAbleStates.Add(CreateDefaultSubobject<UPlayerJumpingState>(TEXT("JumpingState")));
	ActiveAbleStates.Add(CreateDefaultSubobject<UPlayerSprintingState>(TEXT("SprintingState")));
	ActiveAbleStates.Add(CreateDefaultSubobject<UPlayerWalkingState>(TEXT("WalkingState")));


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
	for(int32 i =0; i<ActiveAbleStates.Num(); i++)
	{
		if(ActiveAbleStates[i])
		{
			if(ActiveAbleStates[i]->GetClass()==StateToSearch)
			{
				FoundState=ActiveAbleStates[i];
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

		ActiveAbleStates.AddUnique(LocalNewState);
		LocalNewState->SetPerformingActor(PerformingActor);
		UE_LOG(LogTemp,Warning,TEXT("ActivatableStates %d"),ActiveAbleStates.Num());
	}
}

//get state by gameplayTag
UBaseStateObject* UBaseStateManagerComponent::GetStateOfGameplayTag(FGameplayTag StateGamePlayTag)
{
	 
	for(int32 i=0; i<ActiveAbleStates.Num(); i++)
	{
		if(ActiveAbleStates[i])
		{
			if(ActiveAbleStates[i]->StateGameplayTag==StateGamePlayTag)
			{
				return ActiveAbleStates[i];
				
			}
		}
	}
	return nullptr;
}  

