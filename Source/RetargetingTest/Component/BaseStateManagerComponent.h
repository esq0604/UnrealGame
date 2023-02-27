// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Object/BaseStateObject.h"
#include "BaseStateManagerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UBaseStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseStateManagerComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base Variables")
	TArray<UBaseStateObject*> ActivatableStates;

protected:
	UPROPERTY(BlueprintReadWrite,Category="Base Variables")
	AActor* PerformingActor;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Base Variables")
	UBaseStateObject* CurrentActiveState;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
public:
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void PerformStateOfClass(TSubclassOf<UBaseStateObject> StateToSet);
	
	/* Setter */

	void SetCurrentActiveState(UBaseStateObject* NewCurrentActiveState);
	
	/* Getters */
	UBaseStateObject* GetCurrentActiveState() {return CurrentActiveState;}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	void GetStateOfClass(TSubclassOf<UBaseStateObject> StateToSearch, UBaseStateObject*& FoundState);

	void ConstructStateOfClass(TSubclassOf<UBaseStateObject> StateToConstruct, UBaseStateObject*& ConstructedState);
};
