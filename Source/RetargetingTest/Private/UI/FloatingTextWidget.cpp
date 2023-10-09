// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/FloatingTextWidget.h"

#include "Components/TextBlock.h"


UWidgetAnimation* UFloatingTextWidget::GetFloatUoWidgetAnimation() const
{
	return FloatUp;
}

void UFloatingTextWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UFloatingTextWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	//AnimFinishedDelegate.BindDynamic(this,&UFloatingTextWidget::AnimFinishedDelegateFunction);
	//BindToAnimationFinished(FloatUp,AnimFinishedDelegate);
	PlayAnimation(FloatUp);
}

void UFloatingTextWidget::SetDamageText(const FText& Text)
{
	FloatingDamage->SetText(Text);
}

// void UFloatingTextWidget::AnimFinishedDelegateFunction()
// {
// 	UE_LOG(LogTemp,Warning,TEXT("Anim Finished"));
// 	AnimFinishedDelegateForActor.Execute();
// }
//
// void UFloatingTextWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
// {
// 	Super::OnAnimationFinished_Implementation(Animation);
// }


