// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "TargetingComponent.generated.h"

/**
 *  타게팅관련 기능을 스프링암컴포넌트를 재정의한 클래스에서 구현하고.
 *  해당 TargetingComponent를 가지고있는 객체는 플레이어가 Lock할 수 있도록 구현했습니다.
 */

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UTargetingComponent : public USphereComponent
{
	GENERATED_BODY()

};
