// Copyright Epic Games, Inc. All Rights Reserved.

#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"

#include "DiffUtils.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "RetargetingTest/Component/Public/BasePlayerStatComponent.h"
#include "RetargetingTest/Player/Public/CharaterAnimInstance.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/WidgetComponent.h"
#include "Engine/DamageEvents.h"
#include "Engine/EngineTypes.h"
#include "RetargetingTest/Component/Public/FloatingCombatTextComponent.h"
#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"
#include "RetargetingTest/UI/Public/PlayerStatWidget.h"
#include "GameplayTagContainer.h"
#include "RetargetingTest/Object/Public/BaseStateObject.h"
#include "RetargetingTest/Lib/GameTags.h"
#include "RetargetingTest/Component/Public/Interactable.h"

//////////////////////////////////////////////////////////////////////////
// ARetargetingTestCharacter

ARetargetingTestCharacter::ARetargetingTestCharacter()
	:AttackRange(200.0f) , AttackRadius(50.0f),MaxCombo(4),IsAttacking(false)
{

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

	//사용자 정의 컴포넌트입니다.
	StatComponent= CreateDefaultSubobject<UBasePlayerStatComponent>(TEXT("StatComponent"));
	FloatingTextComponent = CreateDefaultSubobject<UFloatingCombatTextComponent>(TEXT("FloatingDamageComponent"));	
	mStatWidgetComponent=CreateDefaultSubobject<UWidgetComponent>(TEXT("StatBarWidget"));
	StateManagerComponent = CreateDefaultSubobject<UBaseStateManagerComponent>(TEXT("StateManager"));
	StateManagerComponent->SetPerformingActor(this);

}
/**
 * 데미지 전달을 위한 함수입니다. 현재 상태가 Dodge State가 아니라면 데미지를 받습니다.
 * @param DamageAmount - 받는 데미지의 양 입니다.
 *
 */
float ARetargetingTestCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
                                            AController* EventInstigator, AActor* DamageCauser)
{
	if(StateManagerComponent->GetCurrentActiveState()->GetGameplayTag()!=GameTags::Get().State_Dodge)
	{
		float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		StatComponent->SufferDamage(DamageAmount);

		return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

}

/**
 * 플레이어가 공격을 할 시 범위를 확인하기 위해 호출됩니다.
 * @warning  플레이어애님인스턴스의 몽타주애님 노티파이 델리게이트에 바인딩되어 있습니다.
 */
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
/**
 * 게임플레이의 시작 전 초기화 단계입니다.
 * 플레이어의 HP Widget Component의 초기화 후에 뷰포트에 노출해야 하기 때문에 BeginPlay에 작성하였습니다.
 */
void ARetargetingTestCharacter::BeginPlay()
{
	// Call the base class

	Super::BeginPlay();
	//Add Input Mapping Context
	
	StatBarWidget = Cast<UPlayerStatWidget>(mStatWidgetComponent->GetWidget());
	StatBarWidget->BindActorStat(StatComponent);
	StatBarWidget->AddToViewport();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if(Subsystem ==nullptr)
				UE_LOG(LogTemp,Warning,TEXT("Subsystem warning"));
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

/**
 * 현재 속도가 0이면 Idle 상태로 전환합니다. 
 */
void ARetargetingTestCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckForInteractalbe();
}

/**
 * Sprint입력이 끝날때 호출되는 함수입니다. EndState를 통해 다른 상태로 바뀔 수 있습니다.
 */
void ARetargetingTestCharacter::SprintEnd()
{
	if(StateManagerComponent->GetCurrentActiveState()->GetGameplayTag()==FGameplayTag::RequestGameplayTag("State.Sprint"))
	StateManagerComponent->GetCurrentActiveState()->EndState();
}

/**
 *	인벤토리 토글 입력에 대한 매핑 함수 입니다. 
 */
void ARetargetingTestCharacter::ToggleInventory()
{
	UE_LOG(LogTemp,Warning,TEXT("Toggle Inventory"));
}

/**
 *	현재 인터랙터블이 있는 경우 인터랙터블과 상호작용합니다.
 *	TODO : InputMaaping을 해야합니다.
 */
void ARetargetingTestCharacter::Interact()
{
	if(CurrentInteractable!=nullptr)
	{
		CurrentInteractable->Interact_Implementation();
		UE_LOG(LogTemp,Warning,TEXT("Interact"));

	}
}

/**
 * 라인트레이스를 이용해 인터렉터블 아이템이 있는지 확인합니다. 
 */
void ARetargetingTestCharacter::CheckForInteractalbe()
{
	FVector StartTrace = FollowCamera->GetComponentLocation();
	FVector EndTrace = (FollowCamera->GetComponentLocation()*CheckInteractableReach) + StartTrace;

	FHitResult HitResult;

	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(HitResult,StartTrace,EndTrace,ECC_WorldDynamic,CQP);

	AInteractable* PotentialInteractable = Cast<AInteractable>(HitResult.GetActor());

	if(PotentialInteractable ==nullptr)
	{
		HelpText=FString("");
		CurrentInteractable=nullptr;
		return;
	}
	else
	{
		CurrentInteractable=PotentialInteractable;
		HelpText=PotentialInteractable->InteractableHelpText;
	}
}

/**
 * 캐릭터의 IA_Sprint 와 바인딩된 함수입니다. SprintState로 진입합니다.
 * 해당 로직의 문제점은 SprintState로 진입할 수 없을때에도 스태미나를 사용하는것 입니다.
 * 이를 올바르게 처리하기 위해선 Sprint State에서 로직을 처리하는것 입니다.
 */
void ARetargetingTestCharacter::Sprint(const FInputActionValue& Value)
{
	StateManagerComponent->SetCurrentActiveState(StateManagerComponent->GetStateOfGameplayTag(FGameplayTag::RequestGameplayTag("State.Sprint")));
}

UBasePlayerStatComponent* ARetargetingTestCharacter::GetStatComponent() const
{
	return StatComponent;
}

UBaseStateManagerComponent* ARetargetingTestCharacter::GetStateManagerComponent() const
{
	return StateManagerComponent;
}


/**
 * 플레이어의 입력에 대해 함수를 바인딩합니다.
 */
void ARetargetingTestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		// EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		// EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARetargetingTestCharacter::JumpAndDodge);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARetargetingTestCharacter::Move);

		//Looking
		//EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARetargetingTestCharacter::Look);

		//Attack
		EnhancedInputComponent->BindAction(AttackAction,ETriggerEvent::Triggered,this,&ARetargetingTestCharacter::Attack);

		EnhancedInputComponent->BindAction(SprintAction,ETriggerEvent::Triggered, this,&ARetargetingTestCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction,ETriggerEvent::Completed, this,&ARetargetingTestCharacter::SprintEnd);

		//InputComponent->BindAction("AttackAction",IE_Pressed, this, &ARetargetingTestCharacter::Attack);
		EnhancedInputComponent->BindAction(IteractionAction,ETriggerEvent::Triggered,this,&ARetargetingTestCharacter::Interact);
		EnhancedInputComponent->BindAction(ToggleInventoryAction,ETriggerEvent::Triggered,this,&ARetargetingTestCharacter::ToggleInventory);
	}

}
/**
 * 플레이어가 wasd를 통해 움직일때 호출됩니다.
 * @param Value - InputAction에 정의된 값을 매개변수로 받아서 사용합니다.
 */
void ARetargetingTestCharacter::Move(const FInputActionValue& Value)
{
	
	StateManagerComponent->SetCurrentActiveState(StateManagerComponent->GetStateOfGameplayTag(FGameplayTag::RequestGameplayTag("State.Walk")));
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
	//어택 스테이트로 변환합니다.
	// const FGameplayTag AttackingState = FGameplayTag::RequestGameplayTag(TEXT("State.Attack"));
	// if(StateManagerComponent->GetCurrentActiveState()->StateGameplayTag!=AttackingState)
	// {
	// 	StateManagerComponent->SetCurrentActiveState(StateManagerComponent->GetStateOfGameplayTag(AttackingState));
	// }
	
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

/**
 * 캐릭터가 보유한 컴포넌트들의 초기화 시점입니다.애님인스턴스에서 선언한 델리게이트들을 바인딩합니다.
 * 델리게이트에 Lamda를 사용해 다음 공격에 대한 노티파이가 발생한다면 콤보공격을 시작하도록 합니다.
 */
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

/**
 * 콤보 공격을 시작하기 위한 함수입니다.
 */
void ARetargetingTestCharacter::AttackStartComboState()
{
	CanNextCombo=true;
	IsComboInputOn=false;
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo+1,1,MaxCombo);
}

/**
 * 몽타주가 끝나면 콤보공격에 대한 상태들을 초기화합니다.
 */
void ARetargetingTestCharacter::AttackEndComboState()
{
	IsComboInputOn=false;
	CanNextCombo=false;
	CurrentCombo=0;
}

/**
 * 몽타주가 끝나면 콤보공격에 대한 상태들을 초기화합니다.
 */
void ARetargetingTestCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking=false;
	AttackEndComboState();
}

/**
 * Space키에 매핑된 함수입니다. Walk 상태라면 Dodge를, Sprint 상태라면 점프를 수행합니다.
 * 현재 Dodge 입력 매핑은 Blueprint로 되어있습니다.
 */
void ARetargetingTestCharacter::JumpAndDodge()
{
	// if(StateManagerComponent->GetCurrentActiveState()->GetGameplayTag()==FGameplayTag::RequestGameplayTag("State.Walk"))
	// {
	// 	//StateManagerComponent->SetCurrentActiveState(StateManagerComponent->GetStateOfGameplayTag(FGameplayTag::RequestGameplayTag("State.Dodge")));
	// }
	if(StateManagerComponent->GetCurrentActiveState()->GetGameplayTag()==FGameplayTag::RequestGameplayTag("State.Sprint"))
	{
		ACharacter::Jump();
	}
	else
	{
		return;
	}
}



