// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatWidget.h"
#include "PlayerGauge.generated.h"

/**
 * 
 */

class ACharacterBase;
UCLASS()
class RETARGETINGTEST_API UPlayerGauge : public UBaseStatWidget
{
	GENERATED_BODY()

public:
	
	virtual void UpdateHPWidget() override;
	void UpdateStaminaWidget();
	void Init();
	void SetCharacter(ACharacterBase* NewPlayer);
protected:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY()
	UProgressBar* Stamina;
	ACharacterBase* Player;
private:
};
