// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingTextObjectPool.h"


// Sets default values for this component's properties
UFloatingTextObjectPool::UFloatingTextObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFloatingTextObjectPool::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// void UFloatingTextObjectPool::ExpandPool()
// {
// 	for(int i=0; i<EXPAND_POOL_SIZE; i++)
// 	{
// 		AFloatingDamageActor* PooledObject = GetWorld()->SpawnActor<AFloatingDamageActor>()
// 	}
// }


// Called every frame
void UFloatingTextObjectPool::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



