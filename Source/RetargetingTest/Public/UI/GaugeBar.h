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
	void UpdateWidget(float NewPercent, float OldPercent);
	void SetType(EGaugeType Type);
	void SetCharacter(ACharacter* NewCharacter);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;
private:
	EGaugeType mType;

	UPROPERTY()
	ACharacter* mCharacter;
};
