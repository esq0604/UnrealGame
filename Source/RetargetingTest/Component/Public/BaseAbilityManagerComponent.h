// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseAbilityManagerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UBaseAbilityManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseAbilityManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	/* Getters */
	UFUNCTION(BlueprintCallable, Category = "Getters")
	UBaseAbilityObject* GetCurrentActiveAbility();
	
public:
	UPROPERTY(VisibleAnywhere, Category = "Base Variables")
	UBaseAbilityObject* CurrentActiveAbility;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base Variables")
	TArray<UBaseAbilityObject*> ActivatableAbilities;
};
