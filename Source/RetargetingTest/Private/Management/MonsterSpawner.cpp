// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Management/MonsterSpawner.h"

#include "RetargetingTest/Public/Monster/BaseMonster.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ObjectPool=CreateDefaultSubobject<UMonsterObjectPool>(TEXT("ObjectPooler"));

	
}

/**
 * 풀에 몬스터가 꽉찼으면 몬스터를 스폰하도록 델리게이트에 바인딩합니다.
 */
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	ObjectPool->IsFullDieDelegate.BindUObject(this,&AMonsterSpawner::SpawnMonster);
}

/**
 * 풀이 꽉차있다면 몬스터를 스폰하는 함수 입니다.
 */
void AMonsterSpawner::SpawnMonster(bool IsPoolFull)
{
	if(ObjectPool!=nullptr && IsPoolFull)
	{
		for(int i=0; i<ObjectPool->mPoolSize; i++)
		{
			//오브젝트 풀에서 생성된 오브젝트를 가져옵니다.
			//오브젝트의 히든인게임을 비활성화 시키고 콜리전과,틱이벤트를 활성화 시킵니다.
		
			UE_LOG(LogTemp,Warning,TEXT("%s"),*ObjectPool->GetMonsterObject()->GetName());
				ObjectPool->GetMonsterObject()->SetActorHiddenInGame(false);
				ObjectPool->GetMonsterObject()->SetActorEnableCollision(true);
				ObjectPool->GetMonsterObject()->SetActorTickEnabled(true);
			ObjectPool->MonsterPool.Pop();
		}
	}
	ObjectPool->bIsPoolFull=false;
}






