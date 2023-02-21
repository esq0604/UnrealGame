// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FloatingTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UFloatingTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetText();
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	class UTextBlock* DamageText;
};
