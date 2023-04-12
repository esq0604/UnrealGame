// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputDataAsset;
class UInputMappingContext;
class UBaseStateManagerComponent;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); 

public:
	void Move(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void SprintEnd(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void JumpAndDodge(const FInputActionValue& Value);
	void JumpStop(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void ToggleInventory(const FInputActionValue& Value);
	void EquipUnEquip(const FInputActionValue& Value);
	void Init();
	UBaseStateManagerComponent* GetStateManagerComponent() const {return StateManagerComponent;}
protected:
	virtual void BeginPlay() override;
private:
	virtual void SetupInputComponent() override;
	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Enhanced Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Enhanced Input")
	UInputDataAsset* InputAction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="State Manager")
	UBaseStateManagerComponent* StateManagerComponent;
};

