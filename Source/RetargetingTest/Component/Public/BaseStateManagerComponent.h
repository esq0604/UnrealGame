// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseStateManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdatedActiveState);

struct FGameplayTag;
class UBaseStateObject;
class UPlayerIdleState;
class UPlayerSprintingState;
class UPlayerWalkingState;
class UPlayerAttackState;
class UPlayerDodgeState;
class UPlayerWalkingState;
class UPlayerJumpingState;
class UPlayerBlockState;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UBaseStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseStateManagerComponent();
	
	UFUNCTION(BlueprintCallable, Category = "Setters")
	bool TryPerformStateOfClass(TSubclassOf<UBaseStateObject> StateToSet,bool ConditionCheck);

	UFUNCTION(BlueprintCallable, Category = "Setters")
	bool TryPerformStatesOfClass(TArray<TSubclassOf<UBaseStateObject>> StateToSet,bool ConditionCheck);
	
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCanChangeState(bool canChange);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void PerformStateOfClass(TSubclassOf<UBaseStateObject> StateToSet);

	UFUNCTION(BlueprintCallable,Category="Setters")
	void SetPerformingActor(AActor* NewPerformingActor);
	/* Setter */

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetCurrentActiveState(UBaseStateObject* NewCurrentActiveState);
	
	/* Getters */
	UBaseStateObject* GetCurrentActiveState() const; 

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	void GetStateOfClass(TSubclassOf<UBaseStateObject> StateToSearch, UBaseStateObject*& FoundState);

	UFUNCTION(BlueprintCallable, Category = "Getters")
	void ConstructStateOfClass(TSubclassOf<UBaseStateObject> StateToConstruct);

	UFUNCTION(BlueprintCallable)
	UBaseStateObject* GetStateOfGameplayTag(FGameplayTag StateGamePlayTag);

	void StateManagerInit();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Variables")
	TArray<UBaseStateObject*> ActiveAbleStates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Variables")
	TArray<TSubclassOf<UBaseStateObject>> ActiveAbleStatesClass;

	UPROPERTY()
	FOnUpdatedActiveState OnUpdatedDelegate;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Base Variables")
	AActor* PerformingActor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Base Variables")
	UBaseStateObject* CurrentActiveState;

private:
	bool CanChangeState=true;
};
