// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Management/MonsterObjectPool.h"

#include "GameFramework/Actor.h"
#include "RetargetingTest/Public/Monster/BaseMonster.h"
// Sets default values for this component's properties
UMonsterObjectPool::UMonsterObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	MonsterPool.Reserve(mPoolSize);
	// ...
}


/**
 * 몬스터 풀에서 게임 시작시 몬스터를 풀에다 담아놓습니다. 몬스터가 자신의 포인터를 풀에다 넣도록 바인딩합니다.
 */
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
			}
		}
	}
	
}

/**
 * 풀이 비어 있지 않다면 첫번째 오브젝트를 반환합니다.
 * 풀이 비어있으면 nullptr을 반환합니다.
 */
ABaseMonster* UMonsterObjectPool::GetMonsterObject() const
{
	if(MonsterPool.Num() !=0)
	{
		return MonsterPool.Top();
	}
	else
	{
		return nullptr;
	}
}
/**
 * 죽은 몬스터를 풀에 넣습니다. 풀이 꽉찼다면 몬스터를 생성하도록 델리게이트를 했습니다.
 * @param Monster - 풀에 삽입되는 몬스터가 들어갑니다.
 */
void UMonsterObjectPool::InputMonsterToPool(ABaseMonster* Monster)
{
	MonsterPool.Push(Monster);
	if(MonsterPool.Num()==mPoolSize)
	{
		bIsPoolFull=true;
		IsFullDieDelegate.ExecuteIfBound(bIsPoolFull);
	}
}

