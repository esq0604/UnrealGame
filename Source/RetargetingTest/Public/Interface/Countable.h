// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Countable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UCountable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 개수가 있는 아이템은 Countable인터페이스를 상속받아서 샐수있는지에 대한 아이템속성을 갖도록합니다.
 * 이때 해당인터페이스를 상속받는 클래스는 Count변수를 소유하도록합니다.
 */
class RETARGETINGTEST_API ICountable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Interface | Countable")
		int32 GetCont();
		virtual int32 GetCount_Implementation()=0;
	
};	
