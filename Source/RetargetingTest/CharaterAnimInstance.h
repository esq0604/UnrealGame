// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharaterAnimInstance.generated.h"

/**
 * 
 */
 class ARetargetingTestCharacter;
UCLASS()
class RETARGETINGTEST_API UCharaterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	UCharaterAnimInstance(const FObjectInitializer& ObjectInitializer);
	
protected:
	
private:

public:
	
protected:
 	virtual void NativeBeginPlay() override;


private:
	
};
