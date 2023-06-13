// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterObjectPool.generated.h"

//풀이 꽉차면 몬스터가 재생성되도록하는 델리게이트입니다.
DECLARE_DELEGATE_OneParam(PoolIsFullSinature,bool)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RETARGETINGTEST_API UMonsterObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMonsterObjectPool();

	UFUNCTION()
	ABaseMonster* GetMonsterObject() const;

	UFUNCTION()
	void InputMonsterToPool(ABaseMonster* Monster);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	PoolIsFullSinature IsFullDieDelegate;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TObjectPtr<ABaseMonster>> MonsterPool;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	int32 mPoolSize=10;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ABaseMonster> PooledMonster;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	bool bIsPoolFull;
protected:
	
};
