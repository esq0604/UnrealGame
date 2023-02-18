// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackCollision.h"

UAttackCollision::UAttackCollision()
{
	OnComponentBeginOverlap.AddDynamic(this,&UAttackCollision::OnOverlapBegin);
}

void UAttackCollision::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherComp)
	{
		UE_LOG(LogTemp,Warning,TEXT("OnOverlapBegin"));
	}
}
