// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatWidget.h"
#include "Blueprint/UserWidget.h"
#include "MonsterStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UMonsterStatWidget : public UBaseStatWidget
{
	GENERATED_BODY()

public:
	virtual void UpdateHPWidget() override;
protected:
	virtual void NativeConstruct() override;

private:


public:


protected:
	
private:
};
