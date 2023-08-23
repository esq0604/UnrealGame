// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Targeting.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTargeting : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RETARGETINGTEST_API ITargeting
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Targeting")
	void OnTargeted(bool bIsTargeted);
	virtual void OnTargeted_Implementation(bool bIsTargeted)=0;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Targeting")
	bool CanBeTargeted();
	virtual bool CanBeTargeted_Implementation()=0;
};
