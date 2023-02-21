// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatingTextObjectPool.generated.h"

//데미지 풀에서는 처음부터 생성하는것이 아닌, 공격시 생성하고 데미지 풀에 넣습니다.

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UFloatingTextObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFloatingTextObjectPool();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	//AFloatingDamageActor* GetPooledObject();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void ExpandPool();
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<class AFloatingDamageActor*> DamagePool;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	int32 PoolSize;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class AFloatingDamageActor> PooledDamage;

private:
	const int EXPAND_POOL_SIZE =10;
};
