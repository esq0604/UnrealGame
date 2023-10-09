// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Management/ObjectSpawner.h"

#include "Kismet/KismetSystemLibrary.h"
#include "RetargetingTest/Public/Monster/BaseMonster.h"

// Sets default values
AObjectSpawner::AObjectSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ObjectPool=CreateDefaultSubobject<UObjectPool>(TEXT("ObjectPooler"));
}

/**
 * 풀에 몬스터가 꽉찼으면 몬스터를 스폰하도록 델리게이트에 바인딩합니다.
 */
void AObjectSpawner::BeginPlay()
{
	Super::BeginPlay();
	ObjectPool->IsFullDieDelegate.BindUObject(this,&AObjectSpawner::SpawnObject);
}

/**
 * 풀이 꽉차있다면 몬스터를 스폰하는 함수 입니다.
 */
void AObjectSpawner::SpawnObject(bool IsPoolFull)
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
	{
		for(const auto& monster : ObjectPool->Pool)
		{
			//오브젝트 풀에서 생성된 오브젝트를 가져옵니다.
			//오브젝트의 히든인게임을 비활성화 시키고 콜리전과,틱이벤트를 활성화 시킵니다.
			//monster->Init();
			//monster->PostInitializeComponents()
			monster->SetActorHiddenInGame(false);
			monster->SetActorEnableCollision(true);
			monster->SetActorTickEnabled(true);
		}

		while(!ObjectPool->Pool.IsEmpty())
		{
			ObjectPool->Pool.Pop();
		}
	}, ReSpawnTime, false);

}






