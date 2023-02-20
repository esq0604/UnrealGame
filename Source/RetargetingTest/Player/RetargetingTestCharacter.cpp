// Copyright Epic Games, Inc. All Rights Reserved.

#include "RetargetingTestCharacter.h"
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
#include "Engine/DamageEvents.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"


//////////////////////////////////////////////////////////////////////////
// ARetargetingTestCharacter

ARetargetingTestCharacter::ARetargetingTestCharacter()
	:AttackRange(200.0f) , AttackRadius(50.0f)
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
	//mSkeletalMeshComponent=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	mStatComponent= CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));
	//Weapon=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_HeroSword22/SK_Blade_HeroSword22"));
	if(WeaponMesh.Succeeded())
	{
		//Weapon->SetSkeletalMesh(WeaponMesh.Object);
	}
	//Weapon->SetupAttachment(GetMesh(),TEXT("WeaponSocket"));
	//Weapon->SetCollisionProfileName("NoCollsion");
	//애니메이션 인스턴스

}

void ARetargetingTestCharacter::OnAttackCollisionOverlap(UPrimitiveComponent* OverlappedComponent)
{
	//if(bEnableAttackCollision)
		//ApplyAttackDamage();
}


float ARetargetingTestCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
                                            AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp,Warning,TEXT("Actor %s took Damage %d"),*GetName(), FinalDamage);
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
			HitResult.GetActor()->TakeDamage(50.0f,DamageEvent,GetController(),this);
			//UGameplayStatics::ApplyDamage(HitResult.GetActor(),)
			//UGameplayStatics::ApplyPointDamage(HitResult.GetActor(),50.0f,HitResult.GetActor()->GetActorLocation(),HitResult,nullptr,this,nullptr);
			//HitResult.GetActor()->Dama
			//UGameplayStatics::ApplyDamage(HitResult.GetActor(),50.0f)
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Hit result none"));

	}
}

void ARetargetingTestCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("Character In BeginPlay"));
	//Add Input Mapping Context
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

	if(mAnimInstance!=nullptr)
	{
		mAnimInstance->PlayAttackMontage();
	}

	
	//AttackAction->
}

void ARetargetingTestCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	mAnimInstance = Cast<UCharaterAnimInstance>(GetMesh()->GetAnimInstance());
	if(mAnimInstance != nullptr)
	{
		//mAnimInstance->OnMontageEnded.AddDynamic(this,&ARetargetingTestCharacter::OnAttackMontageEnded);
		mAnimInstance->OnAttackHitCheck.AddUObject(this,&ARetargetingTestCharacter::AttackCheck);
	}
}




