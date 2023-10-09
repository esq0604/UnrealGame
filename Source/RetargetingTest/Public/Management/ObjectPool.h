// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPool.generated.h"

//풀이 꽉차면 몬스터가 재생성되도록하는 델리게이트입니다.
DECLARE_DELEGATE_OneParam(PoolIsFullSinature,bool)

UENUM()
enum class POOL_TYPE
{
	Projectile,
	Monster,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RETARGETINGTEST_API UObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPool();

	UFUNCTION()
	AActor* GetPoolObject() const;

	UFUNCTION()
	void InputObjectToPool(AActor* Object);

	void SetType(POOL_TYPE PoolType);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	PoolIsFullSinature IsFullDieDelegate;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> Pool;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	int32 mPoolSize=10;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AActor> PooledObject;
protected:

private:
	POOL_TYPE Type;
};
