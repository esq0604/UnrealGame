// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Interface/Countable.h"
#include "RetargetingTest/Public/Interface/Useable.h"
#include "Potion.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API APotion : public AItemBase, public IUseable, public ICountable
{
	GENERATED_BODY()

public:
	virtual void UseItem_Implementation(ACharacterBase* Character) override;
	virtual int32 GetCount_Implementation() override;
private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=ture))
	float RecoveryAmount=10.0f;

	//Countable Interface를 상속받은 클래스는 개수가 있어야합니다.
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=ture))
	int32 Count;

};
