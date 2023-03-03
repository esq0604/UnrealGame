// Copyright Epic Games, Inc. All Rights Reserved.

#include "RetargetingTestCharacter.h"

#include <string>

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Component/StatComponent.h"
#include "CharaterAnimInstance.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/WidgetComponent.h"
#include "Engine/DamageEvents.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "RetargetingTest/Component/FloatingCombatTextComponent.h"
#include "RetargetingTest/Component/PlayerStatComponent.h"
#include "RetargetingTest/Management/FloatingTextObjectPool.h"
#include "RetargetingTest/Component/BaseStateManagerComponent.h"
#include "RetargetingTest/UI/PlayerHPWidget.h"
#include "GameplayTagContainer.h"
#include "RetargetingTest/Object/BaseStateObject.h"


//////////////////////////////////////////////////////////////////////////
// ARetargetingTestCharacter

ARetargetingTestCharacter::ARetargetingTestCharacter()
	:AttackRange(200.0f) , AttackRadius(50.0f),MaxCombo(4),IsAttacking(false)
{
	StateManagerComponent = CreateDefaultSubobject<UBaseStateManagerComponent>(TEXT("StateManager"));
	StateManagerComponent->SetPerformingActor(this);
	//StateManagerComponent->Perform
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	StatComponent= CreateDefaultSubobject<UPlayerStatComponent>(TEXT("StatComponent"));
	FloatingTextComponent = CreateDefaultSubobject<UFloatingCombatTextComponent>(TEXT("FloatingDamageComponent"));	

	mHPWidgetComponent=CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));

}

float ARetargetingTestCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
                                            AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	StatComponent->GetDamaged(DamageAmount);

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ARetargetingTestCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None,false,this);
	bool bResult=GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation()+GetActorForwardVector()*200.0f,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(50.0f),
		Params
	);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector()*AttackRange;
	FVector Center = GetActorLocation() + TraceVec*0.5f;
	float HalfHeight = AttackRange* 0.5f +AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 3.0f;

	DrawDebugCapsule(GetWorld()
		,Center
		,HalfHeight
		,AttackRadius
		,CapsuleRot
		,DrawColor
		,false
		,DebugLifeTime
		);
#endif
	
	if(bResult)
	{
		if(HitResult.GetActor()->ActorHasTag("Monster"))
		{
			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(StatComponent->GetAttackDamage(),DamageEvent,GetController(),this);
			//플러팅텍스트를 스폰합니다.
			FText AttackDamage = FText::FromString(FString::SanitizeFloat(StatComponent->GetAttackDamage()));
			FloatingTextComponent->AddFloatingActor(AttackDamage,HitResult.GetActor()->GetActorLocation());
		}
	}
}

void ARetargetingTestCharacter::BeginPlay()
{
	// Call the base class

	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("Character In BeginPlay"));
	//Add Input Mapping Context
	HPBarWidget = Cast<UPlayerHPWidget>(mHPWidgetComponent->GetWidget());
	HPBarWidget->BindCharacterStat(StatComponent);
	HPBarWidget->AddToViewport();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if(Subsystem ==nullptr)
				UE_LOG(LogTemp,Warning,TEXT("Subsystem warning"));
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	UE_LOG(LogTemp,Warning,TEXT("%d"),GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	

}

void ARetargetingTestCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}




//////////////////////////////////////////////////////////////////////////
// Input

void ARetargetingTestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARetargetingTestCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARetargetingTestCharacter::Look);

		//Attack
		EnhancedInputComponent->BindAction(AttackAction,ETriggerEvent::Triggered,this,&ARetargetingTestCharacter::Attack);
		
		//InputComponent->BindAction("AttackAction",IE_Pressed, this, &ARetargetingTestCharacter::Attack);
		
	}

}

void ARetargetingTestCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	//FGameplayTag walk=FGameplayTag::RequestGameplayTag(TEXT("State.Walk"));
	IsMoving=true;
	//현재 walk 스테이트가 아니고, walk 스테이트로 가능하다면 스테이트를 변경합니다,.
	FGameplayTag WalkStateTag = FGameplayTag::RequestGameplayTag(TEXT("State.Walk"));
	if(StateManagerComponent->GetCurrentActiveState()!=StateManagerComponent->GetStateOfGameplayTag(WalkStateTag))
	{
		if(StateManagerComponent->GetStateOfGameplayTag(WalkStateTag)->CanPerformState())
		StateManagerComponent->SetCurrentActiveState(StateManagerComponent->ActiveAbleStates[0]);
	}
		FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ARetargetingTestCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ARetargetingTestCharacter::Attack(const FInputActionValue& Value)
{
	IsMoving=false;
	if(IsAttacking)
	{
		if(CanNextCombo)
		{
			IsComboInputOn=true;
		}
	}
	else
	{
		AttackStartComboState();
		mAnimInstance->PlayAttackMontage();
		IsAttacking=true;
	}
}

void ARetargetingTestCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	mAnimInstance = Cast<UCharaterAnimInstance>(GetMesh()->GetAnimInstance());
	if(mAnimInstance != nullptr)
	{
		mAnimInstance->OnAttackHitCheck.AddUObject(this,&ARetargetingTestCharacter::AttackCheck);
		mAnimInstance->OnMontageEnded.AddDynamic(this,&ARetargetingTestCharacter::OnAttackMontageEnded);
		mAnimInstance->OnNextAttackHitCheck.AddLambda([this]()->void
		{
			CanNextCombo=false;
			if(IsComboInputOn)
			{
				AttackStartComboState();
				mAnimInstance->JumpToAttackMontageSection(CurrentCombo);
			}
		});
	}

	
}

void ARetargetingTestCharacter::AttackStartComboState()
{
	CanNextCombo=true;
	IsComboInputOn=false;
	UE_LOG(LogTemp,Warning,TEXT("%d"),FMath::Clamp<int32>(CurrentCombo+1,1,MaxCombo));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo+1,1,MaxCombo);
}

void ARetargetingTestCharacter::AttackEndComboState()
{
	IsComboInputOn=false;
	CanNextCombo=false;
	CurrentCombo=0;
}


void ARetargetingTestCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking=false;
	AttackEndComboState();
}



