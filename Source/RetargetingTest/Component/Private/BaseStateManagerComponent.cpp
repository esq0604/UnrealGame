// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"

#include "RetargetingTest/Object/Public/BaseStateObject.h"
#include "RetargetingTest/Object/Public/PlayerAttackState.h"
#include "RetargetingTest/Object/Public/PlayerDodgeState.h"
#include "RetargetingTest/Object/Public/PlayerIdleState.h"
#include "RetargetingTest/Object/Public/PlayerJumpingState.h"
#include "RetargetingTest/Object/Public/PlayerSprintingState.h"
#include "RetargetingTest/Object/Public/PlayerWalkingState.h"
#include "RetargetingTest/Player//Public/RetargetingTestCharacter.h"


// Sets default values for this component's properties
UBaseStateManagerComponent::UBaseStateManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	ActiveAbleStates.Add(CreateDefaultSubobject<UPlayerDodgeState>(TEXT("DodgeeState")));
	ActiveAbleStates.Add(CreateDefaultSubobject<UPlayerIdleState>(TEXT("IdleState")));
	ActiveAbleStates.Add(CreateDefaultSubobject<UPlayerJumpingState>(TEXT("JumpingState")));
	ActiveAbleStates.Add(CreateDefaultSubobject<UPlayerSprintingState>(TEXT("SprintingState")));
	ActiveAbleStates.Add(CreateDefaultSubobject<UPlayerWalkingState>(TEXT("WalkingState")));
	ActiveAbleStates.Add(CreateDefaultSubobject<UPlayerAttackState>(TEXT("AttackingState")));
}


// Called when the game starts
void UBaseStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	for(auto States : ActiveAbleStates)
	{
		UE_LOG(LogTemp,Warning,TEXT("%s"),*GetOwner()->GetName())
		States->SetPerformingActor(GetOwner());
		States->SetStateManagerComponent(this);
	}
}



void UBaseStateManagerComponent::PerformStateOfClass(TSubclassOf<UBaseStateObject> StateToSet)
{
}

void UBaseStateManagerComponent::SetPerformingActor(AActor* NewPerformingActor)
{
	PerformingActor=NewPerformingActor;
}


void UBaseStateManagerComponent::SetCurrentActiveState(UBaseStateObject* NewCurrentActiveState)
{
	//TODO: 처음 스테이트 상태는 Idle로 지정해놔야하고, nullptr이 있으면안된다.
	if(CurrentActiveState!=nullptr)
		CurrentActiveState->EndState();
	if(NewCurrentActiveState!=nullptr)
	{
		if(NewCurrentActiveState->CanPerformState())
		{
			//TODO : Dodge-> Walk는 바로 전환이 일어나는데 어떻게 해결할래
			CurrentActiveState = NewCurrentActiveState;
			CurrentActiveState->StartState();
		}
	}
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

