// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGaugeWidget.h"
#include "MonsterGauge.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UMonsterGauge : public UBaseGaugeWidget
{
	GENERATED_BODY()

public:
	virtual void UpdateHPWidget(float NewHPPercent) override;
protected:
	virtual void NativeConstruct() override;


};
