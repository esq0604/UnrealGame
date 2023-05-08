// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DemoCharacter.h"

#include "Ability/CharacterAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/DemoPlayerState.h"

ADemoCharacter::ADemoCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0, 0, 70));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->FieldOfView = 80.0f;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	AIControllerClass = APlayerController::StaticClass();

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

void ADemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ADemoCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADemoCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ADemoCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADemoCharacter::LookUpRate);
	PlayerInputComponent->BindAxis("Turn", this, &ADemoCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADemoCharacter::TurnRate);

	BindAscInput();
}

void ADemoCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ADemoPlayerState* PS = GetPlayerState<ADemoPlayerState>();
	if(PS)
	{
		UE_LOG(LogTemp,Warning,TEXT("PossessedBy , PS is valid"));
		InitializeStartingValues(PS);
		AddStartupEffects();
		AddCharacterAbilities();
	}
}

USpringArmComponent* ADemoCharacter::GetCameraBoom()
{
	return CameraBoom;
}

UCameraComponent* ADemoCharacter::GetFollowCamera()
{
	return FollowCamera;
}

float ADemoCharacter::GetStartingCameraBoomArmLength()
{
	return StartingCameraBoomArmLength;
}

FVector ADemoCharacter::GetStartingCameraBoomArmLocation()
{
	return StartingCameraBoomArmLocation;
}

void ADemoCharacter::BeginPlay()
{
	Super::BeginPlay();

	StartingCameraBoomArmLength = CameraBoom->TargetArmLength;
	StartingCameraBoomArmLocation = CameraBoom->GetRelativeLocation();
}

void ADemoCharacter::LookUp(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value);
	}
}

void ADemoCharacter::LookUpRate(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->DeltaTimeSeconds);
	}
}

void ADemoCharacter::Turn(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value);
	}
}

void ADemoCharacter::TurnRate(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
	}
}

void ADemoCharacter::MoveForward(float Value)
{
	if (IsAlive())
	{
		AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0)), Value);
	}
}

void ADemoCharacter::MoveRight(float Value)
{
	if (IsAlive())
	{
		AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, 0)), Value);
	}
}

void ADemoCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	ADemoPlayerState* PS = GetPlayerState<ADemoPlayerState>();
	if(PS)
	{
		InitializeStartingValues(PS);
		BindAscInput();
		InitializeAttributes();
	}
}

void ADemoCharacter::InitializeStartingValues(ADemoPlayerState* PS)
{
	AbilitySystemComponent = Cast<UCharacterAbilitySystemComponent>(PS->GetAbilitySystemComponent());

	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

	AttributeSetBase = PS->GetAttributeSetBase();

	AbilitySystemComponent->SetTagMapCount(DeadTag, 0);
	InitializeAttributes();
	SetHealth(GetMaxHealth());
	SetMana(GetMaxMana());


}

void ADemoCharacter::BindAscInput()
{
	// if(!ASCInputBound && AbilitySystemComponent.IsValid() && IsValid(InputComponent))
	// {
	// 	AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent,FGameplayAbilityInputBinds(FString("ConfirmTarget"),FString("CancelTarget"),FString("DemoAbilityID"),static_cast<int32>(DemoAbilityID::Confirm),static_cast<int32>(DemoAbilityID::Cancel)));
	//
	// 	ASCInputBound=true;
	// }
}
