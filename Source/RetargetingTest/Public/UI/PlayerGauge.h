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
	void UpdateHPWidget(float NewHPPercent, float OldHPPercent);
	void UpdateStaminaWidget(float NewStamPercent, float OldStamPercent);
	void SetCharacter(ACharacterBase* NewPlayer);

	
	UFUNCTION(BlueprintCallable)
	void Init();

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UProgressBar* StaminaProgressBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UProgressBar* HpProgressBar;
	
	ACharacterBase* Player;
public:
	float LerpTime =1.0f;
	float CurrentTime = 0;
private:
	float mNewHpPercent;
	float mOldHpPercent;
	
	float mNewStaminaPercent;
	float mOldStaminaPercent;
};
