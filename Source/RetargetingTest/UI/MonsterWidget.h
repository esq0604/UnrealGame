// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterWidget.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UMonsterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindMonsterStat(class UMonsterStatComponent* NewMonsterStat);
	void UpdateHPWidget();
protected:
	virtual void NativeConstruct() override;

private:


public:
	UPROPERTY()
	class UProgressBar* mHPProgressBar;

protected:
	
private:
	TWeakObjectPtr<class UMonsterStatComponent> CurrentMonsterStat;
};
