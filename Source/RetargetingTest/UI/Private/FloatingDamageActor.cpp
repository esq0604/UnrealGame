// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/FloatingDamageActor.h"

// Sets default values
AFloatingDamageActor::AFloatingDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloatingDamageActor::BeginPlay()
{
	Super::BeginPlay();

	AnchorLocation=GetActorLocation();
}

// Called every frame
void AFloatingDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

