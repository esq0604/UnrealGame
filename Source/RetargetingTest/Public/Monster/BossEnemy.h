// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonster.h"
#include "BossEnemy.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API ABossEnemy : public ABaseMonster
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;


protected:

};
