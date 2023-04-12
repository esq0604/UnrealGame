// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RetargetingTest/Interface/Public/Useable.h"
#include "RetargetingTest/Object/Public/ItemBase.h"
#include "Potion.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API APotion : public AItemBase, public IUseable
{
	GENERATED_BODY()

public:
	virtual void UseItem(ACharacterBase* Character) override;
	virtual void Use(ACharacterBase* Character) override;
private:
	float HpValue=10.0f;

};
