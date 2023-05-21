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
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("PlayerController BeginPlay"));
	const FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
	ACharacterBase* LocalCharacter=Cast<ACharacterBase>(GetPawn());
	APlayerStateBase* LocalPS=Cast<APlayerStateBase>(LocalCharacter->GetPlayerState());
	if(LocalCharacter!=nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("PlayerController BeginPlay GetPawn !nullptr"));
		PlayerHUD=Cast<UPlayerHUD>(CreateWidget(this,PlayerHUDClass));
		if(PlayerHUD!=nullptr)
		PlayerHUD->SetCharacter(LocalCharacter);
		PlayerHUD->Init();
		UE_LOG(LogTemp,Warning,TEXT(""))
		LocalPS->SetPlayerHUD(PlayerHUD);
		PlayerHUD->AddToViewport();
		
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
	EnhancedInputComp->BindAction(InputAction->InputAttack,ETriggerEvent::Started,this,&AMyPlayerController::Attack);
	EnhancedInputComp->BindAction(InputAction->InputLook,ETriggerEvent::Triggered,this,&AMyPlayerController::Look);
	EnhancedInputComp->BindAction(InputAction->InputJumpAndDodge,ETriggerEvent::Triggered,this,&AMyPlayerController::JumpAndDodge);
	EnhancedInputComp->BindAction(InputAction->InputJumpAndDodge,ETriggerEvent::Completed,this,&AMyPlayerController::JumpStop);
	EnhancedInputComp->BindAction(InputAction->InputInteract,ETriggerEvent::Triggered,this,&AMyPlayerController::Interact);
	EnhancedInputComp->BindAction(InputAction->InputToggleInventory,ETriggerEvent::Triggered,this,&AMyPlayerController::ToggleInventory);
	EnhancedInputComp->BindAction(InputAction->InputEquipUnEquip,ETriggerEvent::Triggered,this,&AMyPlayerController::EquipUnEquip);

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

void AMyPlayerController::JumpAndDodge(const FInputActionValue& Value)
{
	//GetCharacter()->Jump();
}

void AMyPlayerController::JumpStop(const FInputActionValue& Value)
{
	GetCharacter()->StopJumping();
}


void AMyPlayerController::Interact(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp,Warning,TEXT("Interact"));
}

void AMyPlayerController::ToggleInventory(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("ToggleInven"));
	PlayerHUD->ToggleInventory();
}

void AMyPlayerController::EquipUnEquip(const FInputActionValue& Value)
{

}

void AMyPlayerController::Init()
{

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


