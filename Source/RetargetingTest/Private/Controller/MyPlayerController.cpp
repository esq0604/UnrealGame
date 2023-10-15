// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Controller/MyPlayerController.h"

#include <string>

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Component/CustomSpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Player/PlayerStateBase.h"
#include "RetargetingTest/RetargetingTest.h"
#include "RetargetingTest/Public/Controller/InputDataAsset.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"
#include "UI/EquipmentUI.h"
#include "UI/PlayerHUD.h"
#include "UI/InventoryUI.h"

AMyPlayerController::AMyPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerHUDClass = UPlayerHUD::StaticClass();

	RollTag=FGameplayTag::RequestGameplayTag("Player.Ability.Roll");
	RollTagContainer.AddTag(RollTag);

	AttackTag = FGameplayTag::RequestGameplayTag("Ability.Attack.Combo");
	AttackTagContainer.AddTag(AttackTag);

	BlockStateTag =FGameplayTag::RequestGameplayTag("Character.IsBlocking");
	BlockTag = FGameplayTag::RequestGameplayTag("Ability.Block");
	BlockTagContainer.AddTag(BlockTag);
	BlockStateTagContainer.AddTag(BlockStateTag);

	InteractTag = FGameplayTag::RequestGameplayTag("Ability.Interact");
	InteractTagContainer.AddTag(InteractTag);

	EquipUnEquipTag=FGameplayTag::RequestGameplayTag("Ability.EquipUnEquip");
	EquipEquipUnEquipTagContainer.AddTag(EquipUnEquipTag);

	JumpTag = FGameplayTag::RequestGameplayTag("Ability.Jump");
	JumpTagContainer.AddTag(JumpTag);

	TargetLookTag = FGameplayTag::RequestGameplayTag("Ability.TargetLook");
	TargetLookTagContainer.AddTag(TargetLookTag);
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerCharacter = Cast<ACharacterBase>(InPawn);
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	const FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
	ACharacterBase* LocalCharacter=Cast<ACharacterBase>(GetPawn());
	APlayerStateBase* LocalPS = Cast<APlayerStateBase>(LocalCharacter->GetPlayerState());
	if(LocalCharacter!=nullptr)
	{
		PlayerHUD=Cast<UPlayerHUD>(CreateWidget(this,PlayerHUDClass));
		if(PlayerHUD)
		{
			PlayerHUD->SetCharacter(LocalCharacter);
			PlayerHUD->Init();
			PlayerHUD->AddToViewport();
		}
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(LocalPS->GetAbilitySystemComponent());
	}
	
	ACharacterBase* OwnerPlayer = Cast<ACharacterBase>(GetCharacter());
	CustomSpringArmComponent = OwnerPlayer->CameraBoom;
	
	UInventoryComponent* InventoryComponent = OwnerPlayer->GetInventoryManagerComponent();
	InventoryUI=Cast<UInventoryUI>(CreateWidget(this,InventoryUIClass));
	EquipmentUI=Cast<UEquipmentUI>(CreateWidget(this,EquipmentUIclass));
	
	if( ensure(InventoryUI) && ensure(EquipmentUI))
	{
		InventoryUI->SetInventoryComponent(InventoryComponent);
		InventoryUI->Init();
		EquipmentUI->SetInventoryComponent(InventoryComponent);
		EquipmentUI->Init();
	}
}

void AMyPlayerController::BindInputASC()
{
	if(!AbilitySystemComponent)
		return;
	FTopLevelAssetPath EnumAssetPath = FTopLevelAssetPath(FName("/Script/RetargetingTest"),FName("EAbilityID"));
	AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent,FGameplayAbilityInputBinds(FString("Confirm"),FString("Cancel"),EnumAssetPath,static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel)));
}
void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping,0);

	UEnhancedInputComponent* EnhancedInputComp= Cast<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComp->BindAction(InputAction->InputSprint,ETriggerEvent::Triggered,this,&AMyPlayerController::Sprint);
	//EnhancedInputComp->BindAction(InputAction->InputAttack,ETriggerEvent::Triggered,this,&AMyPlayerController::Attack);
	EnhancedInputComp->BindAction(InputAction->InputLook,ETriggerEvent::Triggered,this,&AMyPlayerController::Look);
	EnhancedInputComp->BindAction(InputAction->InputJump,ETriggerEvent::Started,this,&AMyPlayerController::Jump);
	//EnhancedInputComp->BindAction(InputAction->InputJump,ETriggerEvent::Completed,this,&AMyPlayerController::JumpStop);
	EnhancedInputComp->BindAction(InputAction->InputInteract,ETriggerEvent::Triggered,this,&AMyPlayerController::Interact);
	EnhancedInputComp->BindAction(InputAction->InputToggleInventory,ETriggerEvent::Started,this,&AMyPlayerController::ToggleInventory);
	EnhancedInputComp->BindAction(InputAction->InputEquipUnEquip,ETriggerEvent::Triggered,this,&AMyPlayerController::EquipUnEquip);
	EnhancedInputComp->BindAction(InputAction->InputRoll,ETriggerEvent::Triggered,this,&AMyPlayerController::Roll);
	EnhancedInputComp->BindAction(InputAction->InputBlock,ETriggerEvent::Triggered,this,&AMyPlayerController::Block);
	EnhancedInputComp->BindAction(InputAction->InputTargetSoftLook,ETriggerEvent::Started,this,&AMyPlayerController::TargetSoftLook);
	EnhancedInputComp->BindAction(InputAction->InputToggleEquipment,ETriggerEvent::Started,this,&AMyPlayerController::ToggleEquipment);
	EnhancedInputComp->BindAction(InputAction->InputTargetHardLock,ETriggerEvent::Started,this,&AMyPlayerController::TargetHardLock);
	BindInputASC();
}

void AMyPlayerController::SendAbilityLocalInput(const FInputActionValue& Value, int32 InputID)
{
	if(!AbilitySystemComponent)
		return;
	
	if(Value.Get<bool>())
	{
		AbilitySystemComponent->AbilityLocalInputPressed(InputID);
	}
	else
	{
		AbilitySystemComponent->AbilityLocalInputReleased(InputID);
	}
}

void AMyPlayerController::Sprint(const FInputActionValue& Value)
{
	SendAbilityLocalInput(Value,static_cast<int32>(EAbilityInputID::Sprint));
}

/**
 * 
 */
// void AMyPlayerController::Attack(const FInputActionValue& Value)
// {
// 	AbilitySystemComponent->TryActivateAbilitiesByTag(AttackTagContainer);
// }

void AMyPlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	// add yaw and pitch input to controller
	if(GetCharacter()!=nullptr)
	{
		if (!CustomSpringArmComponent->IsCameraLockedToTarget())
			GetCharacter()->AddControllerPitchInput(LookAxisVector.Y);

		if (FMath::Abs(LookAxisVector.X) < .1f)
			bAnalogSettledSinceLastTargetSwitch = true;

		if (CustomSpringArmComponent->IsCameraLockedToTarget() && (FMath::Abs(LookAxisVector.X) > TargetSwitchAnalogValue) && bAnalogSettledSinceLastTargetSwitch)
		{
			if (LookAxisVector.X < 0)
				CustomSpringArmComponent->SwitchTarget(EDirection::Left);
			else
				CustomSpringArmComponent->SwitchTarget(EDirection::Right);

			bAnalogSettledSinceLastTargetSwitch = false;
		}
		else
		{
			// calculate delta for this frame from the rate information
			GetCharacter()->AddControllerYawInput(LookAxisVector.X);
		}
	}
}

void AMyPlayerController::Jump(const FInputActionValue& Value)
{
	AbilitySystemComponent->TryActivateAbilitiesByTag(JumpTagContainer);
}

void AMyPlayerController::JumpStop(const FInputActionValue& Value)
{
	GetCharacter()->StopJumping();
}

void AMyPlayerController::Interact(const FInputActionValue& Value)
{
	AbilitySystemComponent->TryActivateAbilitiesByTag(InteractTagContainer);
}

void AMyPlayerController::ToggleInventory(const FInputActionValue& Value)
{
	if(!IsInventoryUIOpen)
	{
		InventoryUI->AddToViewport();
		InventoryUI->SetVisibility(ESlateVisibility::Visible);
		IsInventoryUIOpen=true;
	}
	else
	{
		InventoryUI->RemoveFromParent();
		IsInventoryUIOpen=false;
	}

	if(IsInventoryUIOpen || IsEquipmentUIOpen)
		SetShowMouseCursor(true);
	
	else if(!IsInventoryUIOpen && !IsEquipmentUIOpen)
		SetShowMouseCursor(false);
}

void AMyPlayerController::ToggleEquipment(const FInputActionValue& Value)
{
	if(!IsEquipmentUIOpen)
	{
		EquipmentUI->AddToViewport();
		EquipmentUI->SetVisibility(ESlateVisibility::Visible);
		IsEquipmentUIOpen=true;
	}
	else
	{
		EquipmentUI->RemoveFromParent();
		IsEquipmentUIOpen=false;
	}
	
	if(IsInventoryUIOpen || IsEquipmentUIOpen)
		SetShowMouseCursor(true);
	
	else if(!IsInventoryUIOpen && !IsEquipmentUIOpen)
		SetShowMouseCursor(false);
	
}

void AMyPlayerController::EquipUnEquip(const FInputActionValue& Value)
{
	AbilitySystemComponent->TryActivateAbilitiesByTag(EquipEquipUnEquipTagContainer);
}



void AMyPlayerController::Roll(const FInputActionValue& Value)
{
	AbilitySystemComponent->TryActivateAbilitiesByTag(RollTagContainer);
}

UPlayerHUD* AMyPlayerController::GetPlayerHUD() const
{
	if(PlayerHUD!=nullptr)
	{
		return PlayerHUD;
	}

	return nullptr;
}

UGaugeBar* AMyPlayerController::GetGauge(EGaugeType Type) const
{
	return PlayerHUD->GetGauge(Type);
}

UEquipmentUI* AMyPlayerController::GetEquipmentUI() const
{
	return EquipmentUI;
}

UInventoryUI* AMyPlayerController::GetInventoryUI() const
{
	return InventoryUI;
}

void AMyPlayerController::Block(const FInputActionValue& Value)
{
	SendAbilityLocalInput(Value,static_cast<int32>(EAbilityInputID::RightClickAbility));
}

void AMyPlayerController::TargetSoftLook(const FInputActionValue& Value)
{
	OwnerCharacter->CameraBoom->ToggleSoftLock();
}

void AMyPlayerController::TargetHardLock(const FInputActionValue& Value)
{
	OwnerCharacter->CameraBoom->ToggleCameraLock();
}


