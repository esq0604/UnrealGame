// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerGauge.generated.h"

/**
 * 
 */
class UProgressBar;
class ACharacterBase;
UCLASS()
class RETARGETINGTEST_API UPlayerGauge : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateHPWidget(float NewHPPercent);
	void UpdateStaminaWidget(float NewStaminaPercent);
	void SetCharacter(ACharacterBase* NewPlayer);

	UFUNCTION(BlueprintCallable)
	void Init();

protected:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UProgressBar* StaminaProgressBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UProgressBar* HpProgressBar;
	
	ACharacterBase* Player;
private:
};
