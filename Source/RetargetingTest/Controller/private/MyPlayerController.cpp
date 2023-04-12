// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Controller/public//MyPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "RetargetingTest/Controller/public/InputDataAsset.h"
#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"
#include "RetargetingTest/Object/Public/BaseStateObject.h"
#include "RetargetingTest/Player/Public/CharacterBase.h"

AMyPlayerController::AMyPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StateManagerComponent=CreateDefaultSubobject<UBaseStateManagerComponent>(TEXT("BaseStateManager"));
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();


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
	EnhancedInputComp->BindAction(InputAction->InputJumpAndDodge,ETriggerEvent::Triggered,this,&AMyPlayerController::JumpAndDodge);
	EnhancedInputComp->BindAction(InputAction->InputJumpAndDodge,ETriggerEvent::Completed,this,&AMyPlayerController::JumpStop);
	EnhancedInputComp->BindAction(InputAction->InputInteract,ETriggerEvent::Triggered,this,&AMyPlayerController::Interact);
	EnhancedInputComp->BindAction(InputAction->InputToggleInventory,ETriggerEvent::Triggered,this,&AMyPlayerController::ToggleInventory);
	EnhancedInputComp->BindAction(InputAction->InputEquipUnEquip,ETriggerEvent::Triggered,this,&AMyPlayerController::EquipUnEquip);

}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("Move State : %s"),*FGameplayTag::RequestGameplayTag("State.Walk").ToString());
	if(StateManagerComponent->GetStateOfGameplayTag(FGameplayTag::RequestGameplayTag("State.Walk"))==nullptr)
		UE_LOG(LogTemp,Warning,TEXT("Can't Load State by GamePlayTag"));
	
	StateManagerComponent->SetCurrentActiveState(StateManagerComponent->GetStateOfGameplayTag(FGameplayTag::RequestGameplayTag("State.Walk")));

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
	if(StateManagerComponent->GetCurrentActiveState()!=nullptr)
	{
		if(StateManagerComponent->GetCurrentActiveState()->GetGameplayTag()==FGameplayTag::RequestGameplayTag("State.Sprint"))
		{
			StateManagerComponent->GetCurrentActiveState()->EndState();
		}
	}
}

void AMyPlayerController::Attack(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("Attack"));
	//StateManagerComponent->TryPerformStateOfClass(StateManagerComponent->GetStateOfGameplayTag(GameTags::Get().State_Attack)->GetClass(),true);

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
	GetCharacter()->Jump();
}

void AMyPlayerController::JumpStop(const FInputActionValue& Value)
{
	GetCharacter()->StopJumping();
}


void AMyPlayerController::Interact(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("Interact"));
}

void AMyPlayerController::ToggleInventory(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("Toggle Inventory"));

}

void AMyPlayerController::EquipUnEquip(const FInputActionValue& Value)
{
	//State를 Equip으로 변경합니다.
	//State를 UnEquip으로 변경합니다.
}

void AMyPlayerController::Init()
{
	ACharacterBase* NewCharacter=dynamic_cast<ACharacterBase*>(GetCharacter());
	if(NewCharacter!=nullptr)
	{
		StateManagerComponent->SetPerformingActor(NewCharacter);
		StateManagerComponent->StateManagerInit();
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Init : NewCharacter nullptr"));
	}
}


