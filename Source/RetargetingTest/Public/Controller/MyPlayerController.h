// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

struct FGameplayTagContainer;
class UCharacterAbilitySystemComponent;
class UInputDataAsset;
class UInputMappingContext;
class UBaseStateManagerComponent;
class UPlayerHUD;
class UPlayerGauge;
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
	//void Attack(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void JumpStop(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void ToggleInventory(const FInputActionValue& Value);
	void EquipUnEquip(const FInputActionValue& Value);
	void Roll(const FInputActionValue& Value);
	void Block(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void BlockEnd(const FInputActionValue& Value);
	void BlockEnd_Implementation(const FInputActionValue& Value);
	void TargetLook(const FInputActionValue& Value);
	UPlayerHUD* GetPlayerHUD() const;
	UPlayerGauge* GetGauge() const;
	//bool 변수가 아닌 나중에 EquipState, Ability에서 수정되어야합니다.
	bool IsEquipWeapon=false;
	
protected:
	virtual void BeginPlay() override;


private:
	virtual void SetupInputComponent() override;
	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="AMyPlayerController | Enhanced Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="AMyPlayerController | Enhanced Input")
	UInputDataAsset* InputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AMyPlayerController | HUD", meta=(AllowPrivateAccess=true))
	TSubclassOf<UPlayerHUD> PlayerHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="AMyPlayerController | HUD", meta=(AllowPrivateAccess=true))
	UPlayerHUD* PlayerHUD;

	UPROPERTY(EditInstanceOnly,BlueprintReadWrite,Category="AMyPlayerController | AbilitySystemComponent" , meta=(AllowPrivateAccess=true))
	UCharacterAbilitySystemComponent* AbilitySystemComponent;

private:
	FGameplayTagContainer RollTagContainer;
	FGameplayTag RollTag;

	FGameplayTagContainer AttackTagContainer;
	FGameplayTag AttackTag;

	FGameplayTagContainer BlockTagContainer;
	FGameplayTag BlockTag;
	
	FGameplayTag BlockStateTag;
	FGameplayTagContainer BlockStateTagContainer;

	FGameplayTag InteractTag;
	FGameplayTagContainer InteractTagContainer;

	FGameplayTag EquipUnEquipTag;
	FGameplayTagContainer EquipEquipUnEquipTagContainer;

	FGameplayTag JumpTag;
	FGameplayTagContainer JumpTagContainer;

	FGameplayTag TargetLookTag;
	FGameplayTagContainer TargetLookTagContainer;
};

