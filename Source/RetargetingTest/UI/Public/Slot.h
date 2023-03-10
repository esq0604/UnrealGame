// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Slot.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API USlot : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 SlotNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Count;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UImage* Img;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* Text;
protected:

};
