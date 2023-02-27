// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"

#include "BaseStateObject.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UBaseStateObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State Properties")
	FGameplayTag StateGameplayTag;

protected:
	UPROPERTY()
	AActor* PerformingActor;

public:
	virtual bool CanPerformState();


	UFUNCTION(BlueprintCallable, Category = "State Setters")
	void SetPerformingActor(AActor* NewPerformingActor) { PerformingActor = NewPerformingActor; }

	UFUNCTION(BlueprintCallable,Category= "State Base Events")
	void ConstructState();
};
