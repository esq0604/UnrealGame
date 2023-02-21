// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingDamageSpawn.h"


// Sets default values
AFloatingDamageSpawn::AFloatingDamageSpawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AFloatingDamageSpawn::SpawnDamage()
{
	
}

// Called when the game starts or when spawned
void AFloatingDamageSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingDamageSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

