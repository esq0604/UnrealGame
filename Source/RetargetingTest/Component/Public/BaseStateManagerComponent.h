// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "BaseStateManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdatedActiveState);
struct FGameplayTag;
class UBaseStateObject;
class UPlayerWalkingState;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UBaseStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseStateManagerComponent();

	UFUNCTION(BlueprintCallable)
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
	UBaseStateObject* GetCurrentActiveState() {return CurrentActiveState;}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	void GetStateOfClass(TSubclassOf<UBaseStateObject> StateToSearch, UBaseStateObject*& FoundState);

	void ConstructStatebyClass(TSubclassOf<UBaseStateObject> StateToConstruct);

	UFUNCTION(BlueprintCallable)
	UBaseStateObject* GetStateOfGameplayTag(FGameplayTag StateGamePlayTag);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Variables")
	TArray<UBaseStateObject*> ActiveAbleStates;

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
