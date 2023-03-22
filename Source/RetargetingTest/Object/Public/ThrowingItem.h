// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RetargetingTest/Interface/Public/Useable.h"
#include "RetargetingTest/Object/Public/ItemBase.h"
#include "ThrowingItem.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API AThrowingItem : public AItemBase,public IUseable
{
	GENERATED_BODY()

	virtual void UseItem(ARetargetingTestCharacter* Character) override;
	virtual void Use(ARetargetingTestCharacter* Character) override;

protected:
};
