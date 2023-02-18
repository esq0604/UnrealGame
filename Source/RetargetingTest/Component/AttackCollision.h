// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "AttackCollision.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UAttackCollision : public UBoxComponent
{
	GENERATED_BODY()

public:
	UAttackCollision();
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
