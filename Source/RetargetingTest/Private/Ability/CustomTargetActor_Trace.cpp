// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/CustomTargetActor_Trace.h"


// Sets default values
ACustomTargetActor_Trace::ACustomTargetActor_Trace()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACustomTargetActor_Trace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomTargetActor_Trace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACustomTargetActor_Trace::ConfirmTargetingAndContinue()
{
	Super::ConfirmTargetingAndContinue();
}

