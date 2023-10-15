// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UCustomSpringArmComponent;
class ACharacterBase;
class UEquipmentUI;
class UAbilitySystemComponent;
class UGaugeBar;
struct FGameplayTagContainer;
class UInputDataAsset;
class UInputMappingContext;
class UBaseStateManagerComponent;
class UInventoryUI;
class UPlayerHUD;
struct FInputActionValue;
enum class EGaugeType;
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
	virtual void OnPossess(APawn* InPawn) override;
	//Input Biund Function 
	void Sprint(const FInputActionValue& Value);
	//void Attack(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void JumpStop(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void ToggleInventory(const FInputActionValue& Value);
	void ToggleEquipment(const FInputActionValue& Value);
	void EquipUnEquip(const FInputActionValue& Value);
	void Roll(const FInputActionValue& Value);
	void Block(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void BlockEnd(const FInputActionValue& Value);
	void TargetSoftLook(const FInputActionValue& Value);
	void TargetHardLock(const FInputActionValue& Value);
	//Getter
	UPlayerHUD* GetPlayerHUD() const;
	UGaugeBar* GetGauge(EGaugeType Type) const;
	UEquipmentUI* GetEquipmentUI() const;
	UInventoryUI* GetInventoryUI() const;
	//bool 변수가 아닌 나중에 EquipState, Ability에서 수정되어야합니다.

	void BindInputASC();
protected:
	virtual void BeginPlay() override;

private:
	virtual void SetupInputComponent() override;
	virtual void SendAbilityLocalInput(const FInputActionValue& Value, int32 InputID);
	
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
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite)
	ACharacterBase* OwnerCharacter;
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

	UPROPERTY()
	UEquipmentUI* EquipmentUI;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,meta=(AllowPrivateAccess=true))
	TSubclassOf<UEquipmentUI> EquipmentUIclass;

	UPROPERTY()
	UInventoryUI* InventoryUI;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,meta=(AllowPrivateAccess=true))
	TSubclassOf<UInventoryUI> InventoryUIClass;

	UPROPERTY()
	UCustomSpringArmComponent* CustomSpringArmComponent;
	
	bool IsEquipmentUIOpen=false;
	bool IsInventoryUIOpen=false;
	bool bAnalogSettledSinceLastTargetSwitch=false;
	float TargetSwitchAnalogValue=.8f;
};



