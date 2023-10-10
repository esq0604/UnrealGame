// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "RetargetingTest/Public/Interface/Useable.h"
#include "ThrowingItem.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API AThrowingItem : public AItemBase,public IUseable
{
	GENERATED_BODY()

	//virtual void UseItem(ACharacterBase* Character) override;
	//virtual void Use(ACharacterBase* Character) override;
	virtual void UseItem_Implementation(ACharacterBase* Character) override;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=ture))
	int32 Count;

	
};
