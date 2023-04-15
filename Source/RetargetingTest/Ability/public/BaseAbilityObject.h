// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "BaseAbilityObject.generated.h"

class UBaseStateManagerComponent;
class UBaseAbilityManagerComponent;
/**
 * 
 */
class UAnimMontage;

UCLASS(Blueprintable)
class RETARGETINGTEST_API UBaseAbilityObject : public UObject
{
	GENERATED_BODY()
public:
	UBaseAbilityObject();

	/* Ability Setters */
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetActiveAbilityMontage(UAnimMontage* NewActiveMontage);
	
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetPerformingActor(AActor* NewPerformingActor);
	
	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetAbilityManagerComponent(UBaseAbilityManagerComponent* NewAbilityManagerComponent) {AbilityManagerComponent=NewAbilityManagerComponent;}

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetStateManagerComponent(UBaseStateManagerComponent* NewStateManagerComponent) {StateManagerComponent=NewStateManagerComponent;} 
	UFUNCTION(BlueprintCallable,Category="Base Function")
	virtual void StartAbility();

	UFUNCTION(BlueprintCallable,Category="Base Function")
	virtual bool CanPerformAbility() ;

	void PlayAbilityMontage(UAnimMontage* Montage);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	FGameplayTag AbilityGameplayTag;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Properties")
	UAnimMontage* ActiveAbilityMontage;

	UPROPERTY()
	AActor* PerformingActor;

	UBaseAbilityManagerComponent* AbilityManagerComponent;
	UBaseStateManagerComponent* StateManagerComponent;
};
