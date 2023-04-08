// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Controller/public//MyPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "RetargetingTest/Controller/public/InputDataAsset.h"
#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"
#include "RetargetingTest/Lib/GameTags.h"
#include "RetargetingTest/Object/Public/BaseStateObject.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"

AMyPlayerController::AMyPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StateManagerComponent=CreateDefaultSubobject<UBaseStateManagerComponent>(TEXT("BaseStateManager"));
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("BeginPlay"));

	ARetargetingTestCharacter* NewCharacter=dynamic_cast<ARetargetingTestCharacter*>(GetCharacter());
	StateManagerComponent->SetPerformingActor(NewCharacter);
	StateManagerComponent->Init();
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

}

void AMyPlayerController::Move(const FInputActionValue& Value)
{

	const FGameplayTag WalkTag=FGameplayTag::RequestGameplayTag("State.Walk");
	StateManagerComponent->SetCurrentActiveState(StateManagerComponent->GetStateOfGameplayTag(WalkTag));

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

	const FGameplayTag SprintTag=FGameplayTag::RequestGameplayTag("State.Sprint");
	UE_LOG(LogTemp,Warning,TEXT("Sprint State Object : %s"),*StateManagerComponent->GetStateOfGameplayTag(SprintTag)->GetName());
	StateManagerComponent->SetCurrentActiveState(StateManagerComponent->GetStateOfGameplayTag(SprintTag));
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
}

void AMyPlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	// add yaw and pitch input to controller
	GetCharacter()->AddControllerYawInput(LookAxisVector.X);
	GetCharacter()->AddControllerPitchInput(LookAxisVector.Y);
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


