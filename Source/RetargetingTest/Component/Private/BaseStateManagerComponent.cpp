// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"
#include "RetargetingTest/Object/Public/BaseStateObject.h"
#include "RetargetingTest/Object/Public/PlayerBlockState.h"


// Sets default values for this component's properties
UBaseStateManagerComponent::UBaseStateManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

bool UBaseStateManagerComponent::TryPerformStateOfClass(TSubclassOf<UBaseStateObject> StateToSet, bool ConditionCheck)
{
	if (StateToSet)
	{
		UBaseStateObject* LocalState = nullptr;
		GetStateOfClass(StateToSet, LocalState);


		if (LocalState)
		{

			if (ConditionCheck)
			{
				if (LocalState->CanPerformState())
				{
					if (CurrentActiveState)
					{

						CurrentActiveState->EndState();

					}

					//LocalState->PrepareStateValues();
					CurrentActiveState = LocalState;
					CurrentActiveState->StartState();
					//OnUpdatedActiveState.Broadcast();
					return true;
				}
			}
			else
			{
				if (CurrentActiveState)
				{
					CurrentActiveState->EndState();
				}

				//LocalState->PrepareStateValues();
				CurrentActiveState = LocalState;
				CurrentActiveState->StartState();
				//OnUpdatedActiveState.Broadcast();
				return true;
			}

			return false;
		}
		else
		{
			ConstructStateOfClass(StateToSet);
			
			if (ConditionCheck)
			{
				if (LocalState->CanPerformState())
				{
					if (CurrentActiveState)
					{

						CurrentActiveState->EndState();

					}

					//LocalState->PrepareStateValues();
					CurrentActiveState = LocalState;
					CurrentActiveState->StartState();
					//OnUpdatedActiveState.Broadcast();
					return true;
				}


			}
			else
			{
				if (CurrentActiveState)
				{

					CurrentActiveState->EndState();

				}

				//LocalState->PrepareStateValues();
				CurrentActiveState = LocalState;
				CurrentActiveState->StartState();
				//OnUpdatedActiveState.Broadcast();
				return true;
			}
		}
	}
	return false;
}

/**
 * 스테이트가 변경이 가능한지에 대한 bool 변수인 CanChangeState를 수정합니다.
 * @param canChange - true시 스테이트 변경이 가능합니다. false시 불가능합니다.
 */
void UBaseStateManagerComponent::SetCanChangeState(bool canChange)
{
	CanChangeState=canChange;
}


// Called when the game starts
void UBaseStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBaseStateManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(CurrentActiveState!=nullptr)
	{
		if(CurrentActiveState->GetHasTickState())
		{
			CurrentActiveState->TickState();
		}
	}
}


void UBaseStateManagerComponent::PerformStateOfClass(TSubclassOf<UBaseStateObject> StateToSet)
{
	
}

/**
 * 현재 수행중인 액터를 결정합니다. StateManagerComponent의 수행중인 액터는 캐릭터 입니다.
 * @param NewPerformingActor - StateManagerComponent를 사용하는 액터가 들어옵니다.
 */
void UBaseStateManagerComponent::SetPerformingActor(AActor* NewPerformingActor)
{
	UE_LOG(LogTemp,Warning,TEXT("SetPerformingActor : %s"),*NewPerformingActor->GetName())
	PerformingActor=NewPerformingActor;
}

/**
 * 활성화 된 상태를 변경합니다.
 * @param NewCurrentActiveState - 새로 변경될 스테이트 객체가 들어옵니다.
 * @warning 몽타주 행위에 대한 스테이트는 노티파이를 통해 CanChangeState가 결정됩니다.(애니메이션 동작시 스테이트 변경못하도록)
 * @warning Sprint,Jump,Walk와 같은 행동들(몽타주를 사용하지 않는 상태들)은 객체 내부에서 CanChangeState가 결정됩니다.
 */
void UBaseStateManagerComponent::SetCurrentActiveState(UBaseStateObject* NewCurrentActiveState)
{
	UE_LOG(LogTemp,Warning,TEXT("NewState %s"),*NewCurrentActiveState->GetGameplayTag().ToString());
	if(CanChangeState)
	{
		if(CurrentActiveState!=nullptr)
		{
			CurrentActiveState->EndState();
		}
		if(NewCurrentActiveState!=nullptr)
		{
			if(NewCurrentActiveState->CanPerformState())
			{
				CurrentActiveState = NewCurrentActiveState;
				UE_LOG(LogTemp,Warning,TEXT("CurrentActivState %s"),*CurrentActiveState->GetGameplayTag().ToString());
				CurrentActiveState->StartState();
			}
		}
	}
}

UBaseStateObject* UBaseStateManagerComponent::GetCurrentActiveState() const
{
	return CurrentActiveState;
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

void UBaseStateManagerComponent::ConstructStateOfClass(TSubclassOf<UBaseStateObject> StateToConstruct)
{
	if(StateToConstruct)
	{
		UBaseStateObject* LocalNewState;
		LocalNewState = NewObject<UBaseStateObject>(GetOwner(),StateToConstruct);
		LocalNewState->SetPerformingActor(PerformingActor);
		LocalNewState->SetStateManagerComponent(this);
		ActiveAbleStates.AddUnique(LocalNewState);
	}
}

/**
 * FGamePlayTag를 통해 스테이트 객체를 반환합니다.
 * @param StateGamePlayTag - 반환받을 객체의 게임플레이 태그가 들어옵니다.
 */
UBaseStateObject* UBaseStateManagerComponent::GetStateOfGameplayTag(FGameplayTag StateGamePlayTag)
{
	for(int32 i=0; i<ActiveAbleStates.Num(); i++)
	{
		if(ActiveAbleStates[i])
		{
			UE_LOG(LogTemp,Warning,TEXT("%d ActiveAbleStates Tag :%s"),i,*ActiveAbleStates[i]->GetGameplayTag().ToString());
			if(ActiveAbleStates[i]->GetGameplayTag()==StateGamePlayTag)
			{
				return ActiveAbleStates[i];
			}
		}
	}
	return nullptr;
}

void UBaseStateManagerComponent::StateManagerInit()
{
	for(UBaseStateObject* state : ActiveAbleStates)
	{
		UE_LOG(LogTemp,Warning,TEXT("Each State SetPerfomingActor %s"),*PerformingActor->GetName());
		state->SetPerformingActor(PerformingActor);
		state->SetStateManagerComponent(this);
	}
}


