// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterObjectPool.h"
#include "RetargetingTest/Monster/BaseMonster.h"
#include "GameFramework/Actor.h"
// Sets default values for this component's properties
UMonsterObjectPool::UMonsterObjectPool()
:mPoolSize(10),bIsPoolFull(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	MonsterPool.Reserve(mPoolSize);
	// ...
}


// Called when the game starts
void UMonsterObjectPool::BeginPlay()
{
	Super::BeginPlay();

	// 처음에는 오브젝트를 스폰하고 이후에는 관리합니다.
	if(PooledMonster != nullptr)
	{
		UWorld* const World = GetWorld();
		if(World)
		{
			for(int i=0; i<mPoolSize; i++)
			{
				ABaseMonster* PooledActor = GetWorld()->SpawnActor<ABaseMonster>(PooledMonster,FVector(i*100,i*100,i),FRotator().ZeroRotator);
				PooledActor->SetActorHiddenInGame(false);
				PooledActor->SetActorEnableCollision(true);
				PooledActor->SetActorTickEnabled(true);
				PooledActor->MonsterDieDelegate.BindUObject(this,&UMonsterObjectPool::InputMonsterToPool);
				//UE_LOG(LogTemp,Warning,TEXT("Added Obejct to the pool %s"),*PooledActor->GetName());
			}
		}
	}
	
}


// Called every frame
void UMonsterObjectPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ABaseMonster* UMonsterObjectPool::GetMonsterObject()
{
	if(MonsterPool.Num() !=0)
	{
		ABaseMonster* returnVal=MonsterPool.Top();
		return returnVal; 
	}
	else
	{
		//TODO : 오브젝트 풀의 크기를 늘려줍니다.
		UE_LOG(LogTemp,Warning,TEXT("MonsterPool Num is 0"));
		return nullptr;
	}
}

void UMonsterObjectPool::InputMonsterToPool(ABaseMonster* Monster)
{
	MonsterPool.Push(Monster);
	UE_LOG(LogTemp,Warning,TEXT("%s"),*Monster->GetName())
	if(MonsterPool.Num()==mPoolSize)
	{
		bIsPoolFull=true;
		FIsFullDieDelegate.ExecuteIfBound(bIsPoolFull);
		
	}
}

