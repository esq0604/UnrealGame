// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "BaseStateObject.generated.h"

/**
 *
 각 스테이트에서는 해당 스테이트를 수행할 수 있는 조건과
 다음 스테이트로 넘어갈 수 있는 스테이트의 종류를 나열합니다.
 */
class UBaseStateManagerComponent;
UCLASS(Blueprintable)
class RETARGETINGTEST_API UBaseStateObject : public UObject
{
	GENERATED_BODY()

public:
	UBaseStateObject();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State Properties")
	FGameplayTag StateGameplayTag;

protected:
	UPROPERTY()
	AActor* PerformingActor;

	UPROPERTY()
	UBaseStateManagerComponent* StateManagerComponent;
public:
	UFUNCTION()
	virtual bool CanPerformState();

	UFUNCTION()
	virtual void StartState();
	
	UFUNCTION()
	virtual void EndState();
	UFUNCTION(BlueprintCallable, Category = "State Setters")
	void SetPerformingActor(AActor* NewPerformingActor) { PerformingActor = NewPerformingActor; }

	UFUNCTION(BlueprintCallable,Category= "State Base Events")
	void ConstructState();

	void SetStateManagerComponent(UBaseStateManagerComponent* NewStateManagerComponent) {StateManagerComponent=NewStateManagerComponent;}
	UBaseStateManagerComponent* GetStateManagerComponent() {return StateManagerComponent;}

	FGameplayTag GetGameplayTag() {return StateGameplayTag;}
};
