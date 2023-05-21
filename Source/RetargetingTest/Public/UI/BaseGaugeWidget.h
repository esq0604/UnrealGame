// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseGaugeWidget.generated.h"

/**
 * 캐릭터의 피, 마나  or 몬스터의 피 에 대한 위젯의 부모클래스입니다.
 */
UCLASS()
class RETARGETINGTEST_API UBaseGaugeWidget : public UUserWidget
{
	GENERATED_BODY()
public:

protected:
	virtual void UpdateHPWidget(float NewHPPercent);
	virtual void NativeConstruct() override; 

protected:


};
