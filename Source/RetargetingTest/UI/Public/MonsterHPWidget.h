// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHPWidget.h"
#include "Blueprint/UserWidget.h"
#include "MonsterHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UMonsterHPWidget : public UBaseHPWidget
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
