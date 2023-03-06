// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatComponent.h"
#include "Components/ActorComponent.h"
#include "BasePlayerStatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UBasePlayerStatComponent : public UBaseStatComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBasePlayerStatComponent();

protected:

public:
private:

};
