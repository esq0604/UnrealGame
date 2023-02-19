// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterObjectPool.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawner.generated.h"
class UMonsterPool;

UCLASS()
class RETARGETINGTEST_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMonsterSpawner();

	UFUNCTION()
	void SpawnMonster(bool IsPoolFull);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMonsterObjectPool* ObjectPool;

	
};
