// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterObjectPool.generated.h"

DECLARE_DELEGATE_OneParam(FPoolIsFullSinature,bool)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RETARGETINGTEST_API UMonsterObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMonsterObjectPool();

	UFUNCTION()
	ABaseMonster* GetMonsterObject();

	UFUNCTION()
	void InputMonsterToPool(ABaseMonster* Monster);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<class ABaseMonster*> MonsterPool;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	int32 mPoolSize;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class ABaseMonster> PooledMonster;

	
	FPoolIsFullSinature FIsFullDieDelegate;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	bool bIsPoolFull;
protected:
	
};
