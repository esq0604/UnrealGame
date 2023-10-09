// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Controller/MyPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Ability/CustomAbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
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
	
	ACharacterBase* OwerPlayer = Cast<ACharacterBase>(GetCharacter());
	InventoryUI=Cast<UInventoryUI>(CreateWidget(this,InventoryUIClass));
	EquipmentUI=Cast<UEquipmentUI>(CreateWidget(this,EquipmentUIclass));
	if(ensure(OwerPlayer) && ensure(InventoryUI) && ensure(EquipmentUI))
	{
		InventoryUI->SetCharacter(OwerPlayer);
		InventoryUI->Init();
		EquipmentUI->SetCharacter(OwerPlayer);
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
	//EnhancedInputComp->BindAction(InputAction->InputBlock,ETriggerEvent::Started,this,&AMyPlayerController::Block);
	EnhancedInputComp->BindAction(InputAction->InputTargetLook,ETriggerEvent::Started,this,&AMyPlayerController::TargetLook);
	EnhancedInputComp->BindAction(InputAction->InputToggleEquipment,ETriggerEvent::Started,this,&AMyPlayerController::ToggleEquipment);
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
		GetCharacter()->AddControllerYawInput(LookAxisVector.X);
		GetCharacter()->AddControllerPitchInput(LookAxisVector.Y);
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
	///PlayerHUD->ToggleInventory();
	
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
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("PlayerController GetPlayerHUD nullptr"));
		return nullptr;
	}
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
//	AbilitySystemComponent->TryActivateAbilitiesByTag(BlockTagContainer);
}

void AMyPlayerController::TargetLook(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp,Warning,TEXT("Target Look "));
	//AbilitySystemComponent->TryActivateAbilitiesByTag(TargetLookTagContainer);
}


