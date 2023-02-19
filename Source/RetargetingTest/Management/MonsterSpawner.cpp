// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
//#include "MonsterPool.h"
#include "RetargetingTest/Monster/BaseMonster.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ObjectPool=CreateDefaultSubobject<UMonsterObjectPool>(TEXT("ObjectPooler"));

	
}

void AMonsterSpawner::SpawnMonster(bool IsPoolFull)
{
	if(ObjectPool && IsPoolFull)
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

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	ObjectPool->FIsFullDieDelegate.BindUObject(this,&AMonsterSpawner::SpawnMonster);
	if(ObjectPool)
	{
		for(int i=0; i<ObjectPool->mPoolSize; i++)
		{
			//오브젝트 풀에서 생성된 오브젝트를 가져옵니다.
			//오브젝트의 히든인게임을 비활성화 시키고 콜리전과,틱이벤트를 활성화 시킵니다.
			// ObjectPool->GetMonsterObject()->SetActorHiddenInGame(false);
			// ObjectPool->GetMonsterObject()->SetActorEnableCollision(true);
			// ObjectPool->GetMonsterObject()->SetActorTickEnabled(true);
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("obejct pool is not valid"));
	}
}





