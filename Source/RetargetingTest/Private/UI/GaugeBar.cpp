// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GaugeBar.h"

#include "Components/ProgressBar.h"



void UGaugeBar::UpdateWidget(float NewPercent, float OldPercent)
{
	ProgressBar->SetPercent(NewPercent);
}

void UGaugeBar::SetType(EGaugeType Type)
{
	mType=Type;
}

void UGaugeBar::SetCharacter(ACharacter* NewCharacter)
{
	mCharacter=NewCharacter;
}

