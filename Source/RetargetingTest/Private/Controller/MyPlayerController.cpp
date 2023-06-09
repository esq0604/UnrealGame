// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Controller/MyPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InterchangeResult.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "Player/PlayerStateBase.h"
#include "RetargetingTest/Public/Controller/InputDataAsset.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"
#include "UI/PlayerHUD.h"

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
		if(PlayerHUD!=nullptr)
		PlayerHUD->SetCharacter(LocalCharacter);
		PlayerHUD->Init();
		PlayerHUD->AddToViewport();
		AbilitySystemComponent= LocalPS->GetAbilitySystemComponent();
	}

}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping,0);

	UEnhancedInputComponent* EnhancedInputComp= Cast<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComp->BindAction(InputAction->InputMove,ETriggerEvent::Triggered,this,&AMyPlayerController::Move);
	EnhancedInputComp->BindAction(InputAction->InputSprint,ETriggerEvent::Triggered,this,&AMyPlayerController::Sprint);
	EnhancedInputComp->BindAction(InputAction->InputSprint,ETriggerEvent::Completed,this,&AMyPlayerController::SprintEnd);
	EnhancedInputComp->BindAction(InputAction->InputAttack,ETriggerEvent::Triggered,this,&AMyPlayerController::Attack);
	EnhancedInputComp->BindAction(InputAction->InputLook,ETriggerEvent::Triggered,this,&AMyPlayerController::Look);
	EnhancedInputComp->BindAction(InputAction->InputJump,ETriggerEvent::Started,this,&AMyPlayerController::Jump);
	//EnhancedInputComp->BindAction(InputAction->InputJump,ETriggerEvent::Completed,this,&AMyPlayerController::JumpStop);
	EnhancedInputComp->BindAction(InputAction->InputInteract,ETriggerEvent::Triggered,this,&AMyPlayerController::Interact);
	EnhancedInputComp->BindAction(InputAction->InputToggleInventory,ETriggerEvent::Triggered,this,&AMyPlayerController::ToggleInventory);
	EnhancedInputComp->BindAction(InputAction->InputEquipUnEquip,ETriggerEvent::Triggered,this,&AMyPlayerController::EquipUnEquip);
	EnhancedInputComp->BindAction(InputAction->InputRoll,ETriggerEvent::Triggered,this,&AMyPlayerController::Roll);
	EnhancedInputComp->BindAction(InputAction->InputBlock,ETriggerEvent::Started,this,&AMyPlayerController::Block);
	EnhancedInputComp->BindAction(InputAction->InputBlock,ETriggerEvent::Canceled,this,&AMyPlayerController::BlockEnd);
	EnhancedInputComp->BindAction(InputAction->InputTargetLook,ETriggerEvent::Started,this,&AMyPlayerController::TargetLook);
}
void AMyPlayerController::Move(const FInputActionValue& Value)
{
	//const FGameplayTag LocalWalkTag=FGameplayTag::RequestGameplayTag("State.Walk");	
	//UBaseStateObject* LocalWalkState=StateManagerComponent->GetStateOfGameplayTag(LocalWalkTag);
	//StateManagerComponent->TryPerformStateOfClass(LocalWalkState->GetClass(),true);

	FVector2D MovementVector = Value.Get<FVector2D>();
	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	GetCharacter()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetCharacter()->AddMovementInput(RightDirection, MovementVector.X);
	
}

void AMyPlayerController::Sprint(const FInputActionValue& Value)
{
	//const FGameplayTag SprintTag = FGameplayTag::RequestGameplayTag("State.Sprint");
	//StateManagerComponent->TryPerformStateOfClass(StateManagerComponent->GetStateOfGameplayTag(SprintTag)->GetClass(),true);
}

void AMyPlayerController::SprintEnd(const FInputActionValue& Value)
{

}
/**
 * TODO: 해당 함수에서 IsEquipWeapon 변수를 사용하지 않도록 상태시스템을 수정해야합니다.
 * 
 */
void AMyPlayerController::Attack(const FInputActionValue& Value)
{
	AbilitySystemComponent->TryActivateAbilitiesByTag(AttackTagContainer);
}

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
	PlayerHUD->ToggleInventory();
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

UPlayerGauge* AMyPlayerController::GetGauge() const
{
	return PlayerHUD->GetGauge();
}

void AMyPlayerController::Block(const FInputActionValue& Value)
{
	AbilitySystemComponent->TryActivateAbilitiesByTag(BlockTagContainer);
}

void AMyPlayerController::BlockEnd(const FInputActionValue& Value)
{
	AbilitySystemComponent->RemoveActiveEffectsWithGrantedTags(BlockStateTagContainer);
}


void AMyPlayerController::TargetLook(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("Target Look "));
	AbilitySystemComponent->TryActivateAbilitiesByTag(TargetLookTagContainer);
}


