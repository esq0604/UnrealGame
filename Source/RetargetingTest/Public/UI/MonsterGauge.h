// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterGauge.generated.h"

/**
 * 
 */
class UProgressBar;
UCLASS()
class RETARGETINGTEST_API UMonsterGauge : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateHPWidget(float NewHPPercent, float OldHPPercent);

	UFUNCTION(BlueprintCallable)
	void Init();
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	TObjectPtr<UProgressBar> HpProgressBar;
private:
	float CurrentTime=0;
	float LerpTime=1.0f;

private:
	float mNewHpPercent=0;
	float mOldHpPercent=0;
};
