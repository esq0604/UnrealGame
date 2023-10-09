// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Delegates/DelegateCombinations.h"
#include "Delegates/DelegateCombinations.h"
#include "FloatingTextWidget.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_DELEGATE(FAnimFinishedSignature);

class UTextBlock;

UCLASS()
class RETARGETINGTEST_API UFloatingTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UWidgetAnimation* GetFloatUoWidgetAnimation() const;

	void SetDamageText(const FText& Text);
	//
	// UFUNCTION()
	// void AnimFinishedDelegateFunction();
	//
	// UFUNCTION()
	// virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
public:
	FWidgetAnimationDynamicEvent AnimFinishedDelegate;

	FAnimFinishedSignature AnimFinishedDelegateForActor;
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(EditDefaultsOnly,meta=(BindWidget),BlueprintReadOnly)
	TObjectPtr<UTextBlock> FloatingDamage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* FloatUp;

	
};
