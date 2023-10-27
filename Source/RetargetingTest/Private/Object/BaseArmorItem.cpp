// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BaseArmorItem.h"


// Sets default values
ABaseArmorItem::ABaseArmorItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseArmorItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseArmorItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

