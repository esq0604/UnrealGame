// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GaugeBar.generated.h"

class UProgressBar;
/**
 * 
 */
UENUM()
enum class EGaugeType
{
	HP,
	Stamina,
};

UCLASS()
class RETARGETINGTEST_API UGaugeBar : public UUserWidget
{
	GENERATED_BODY()
public:
	UGaugeBar(EGaugeType Type);

	void UpdateWidget();

protected:
	TObjectPtr<UProgressBar> ProgressBar;
private:
	EGaugeType mType;
};
