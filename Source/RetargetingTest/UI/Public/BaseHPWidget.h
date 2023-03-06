// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UBaseHPWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	void BindActorStat(class UBaseStatComponent* NewMonsterStat);

protected:
	virtual void UpdateHPWidget();
	virtual void NativeConstruct() override; 

protected:
	UPROPERTY()
	class UProgressBar* HpProgressBar;

	TWeakObjectPtr<UBaseStatComponent> CurrentActorStat;
private:
};
