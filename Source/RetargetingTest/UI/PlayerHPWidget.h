// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UPlayerHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacterStat(class UPlayerStatComponent* NewMonsterStat);
	void UpdateHPWidget();
protected:
	virtual void NativeConstruct() override;

	
public:
	UPROPERTY()
	class UProgressBar* mHPProgressBar;

	UPROPERTY(EditAnywhere)
	class UPlayerHPWidget* HPBarWidget;
private:
	TWeakObjectPtr<class UPlayerStatComponent> CurrentCharacterStat;
};
