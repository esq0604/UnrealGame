// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "BaseStateObject.generated.h"

class UBaseAbilityManagerComponent;
/**
 *
 각 스테이트에서는 해당 스테이트를 수행할 수 있는 조건과
 다음 스테이트로 넘어갈 수 있는 스테이트의 종류를 나열합니다.
 */
class UBaseStateManagerComponent;
class UBaseAbilityObject;
UCLASS(Blueprintable)
class RETARGETINGTEST_API UBaseStateObject : public UObject
{
	GENERATED_BODY()

public:
	UBaseStateObject();

public:
	UFUNCTION(BlueprintCallable)
	virtual bool CanPerformState();

	UFUNCTION(BlueprintCallable)
	virtual void StartState();

	UFUNCTION(BlueprintCallable)
	virtual void TickState();

	UFUNCTION(BlueprintCallable)
	virtual void EndState();
	
	UFUNCTION(BlueprintCallable, Category = "State Setters")
	void SetPerformingActor(AActor* NewPerformingActor) { PerformingActor = NewPerformingActor; }

	UFUNCTION(BlueprintCallable)
	bool CheckAbilitesToRun(TArray<TSubclassOf<UBaseAbilityObject>> AbilitiesToCheck);

	
	void SetStateManagerComponent(UBaseStateManagerComponent* NewStateManagerComponent) {StateManagerComponent=NewStateManagerComponent;}

	void SetAbilityManagerComponent(UBaseAbilityManagerComponent* NewAbilityManagerComponent) {AbilityManagerComponent = NewAbilityManagerComponent;}

	UBaseStateManagerComponent* GetStateManagerComponent() const {return StateManagerComponent;}

	FGameplayTag GetGameplayTag() const {return StateGameplayTag;}

	bool GetHasTickState() const;
	
	void SetGameplayTag(const FGameplayTag& GameplayTag);

protected:
	UFUNCTION(BlueprintCallable,Category="Getter")
	AActor* GetPerformingActor() const {return PerformingActor;}
protected:
	UPROPERTY()
	AActor* PerformingActor;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
	UBaseStateManagerComponent* StateManagerComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
	UBaseAbilityManagerComponent* AbilityManagerComponent;
	
	FGameplayTag StateGameplayTag;

	bool HasTickState;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UBaseAbilityObject> SelectedAbilityToTrigger;
};
