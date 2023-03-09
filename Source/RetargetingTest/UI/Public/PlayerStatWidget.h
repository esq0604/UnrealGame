// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatWidget.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatWidget.generated.h"

/**
 * 
 */

UCLASS()
class RETARGETINGTEST_API UPlayerStatWidget : public UBaseStatWidget
{
	GENERATED_BODY()

public:
	
	virtual void UpdateHPWidget() override;
	void UpdateStaminaWidget();
	virtual void BindActorStat(UBaseStatComponent* NewActorStat) override;
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	UProgressBar* Stamina;

private:
};
