// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbilityObject.h"
#include "UObject/Object.h"
#include "BasePlayerAbility.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UBasePlayerAbility : public UBaseAbilityObject
{
	GENERATED_BODY()

public:
	UBasePlayerAbility();

	virtual void EndAbility() override;
protected:
	UFUNCTION(BlueprintCallable,Category="Getter")
	TArray<UAnimMontage*> GetAbilityMontage(TSubclassOf<UBaseAbilityObject> AbilityToLookFor); 

};
