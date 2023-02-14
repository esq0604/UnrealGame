// Fill out your copyright notice in the Description page of Project Settings.


#include "CharaterAnimInstance.h"
#include "RetargetingTestCharacter.h"
UCharaterAnimInstance::UCharaterAnimInstance(const FObjectInitializer& ObjectInitializer)
{
}

void UCharaterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	// character=Cast<ARetargetingTestCharacter>(GetOwningActor());
	// bIsTrunLeft=character->GetIsTurnLeft();
	// bIsTrunRight=character->GetIsTurnRight();
}
