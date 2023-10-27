// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class ACharacterBase;

UENUM()
enum class EInteractableType : uint8
{
	PickUp				UMETA(DisplayName = "PickUp"),
	NonPlayerCharacter	UMETA(DisplayName = "NonPlayerCharacter"),
	Device				UMETA(DisplayName = "Device"),
	Toggle				UMETA(DisplayName = "Toggle"),
	Container			UMETA(DisplayName = "Container"),
};

USTRUCT()
struct FInteractableData
{
	GENERATED_BODY()

	FInteractableData() :
	InteractableType(EInteractableType::PickUp),
	Name(FText::GetEmpty()),
	Action(FText::GetEmpty()),
	Quantity(0),
	InterfaceDuration(0.f)
	{
		
	};

	UPROPERTY(EditDefaultsOnly)
	EInteractableType InteractableType;

	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	FText Action;

	//픽업 아이템에만 사용됩니다.
	UPROPERTY(EditDefaultsOnly)
	int8 Quantity;

	//문을 일정시간동안 여는 등 인터렉션에 타이머가 필요한 경우 사용됩니다.
	UPROPERTY(EditDefaultsOnly)
	float InterfaceDuration;
	
};
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class RETARGETINGTEST_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BeginFocus();
	virtual void EndFocus();
	virtual void BeginInteraction();
	virtual void EndInteraction();
	virtual void Interact(ACharacterBase* PlayerCharacter);

	FInteractableData InteractableData;
};
