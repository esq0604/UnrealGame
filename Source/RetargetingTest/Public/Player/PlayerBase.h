// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerBase.generated.h"

UCLASS()
class RETARGETINGTEST_API APlayerBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
