// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/CharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"

#include "AbilitySystemComponent.h"
#include "MotionWarpingComponent.h"
#include "Camera/CameraComponent.h"
#include "Component/InventoryComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerStateBase.h"
#include "RetargetingTest/Public/Component/FloatingCombatTextComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/CharaterAnimInstance.h"
//////////////////////////////////////////////////////////////////////////
// ARetargetingTestCharacter

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
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
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	//사용자 정의 컴포넌트입니다.
	FloatingTextComponent = CreateDefaultSubobject<UFloatingCombatTextComponent>(TEXT("FloatingDamageComponent"));
	
	MotionWarpComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpComponent"));

	InventoryManagerComponent =CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryManagerComponent"));

	Weapon=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon StaticMesh Component"));
	WeaponCollision=CreateDefaultSubobject<UCapsuleComponent>(TEXT("Weapon Collision"));
	WeaponCollision->SetupAttachment(Weapon);
}

void ACharacterBase::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();
	AnimInstance=Cast<UCharaterAnimInstance>(GetMesh()->GetAnimInstance());
	Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,"Weapon_R");
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this,&ACharacterBase::WeaponCollisionBeginOverlap);
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(TargetLock)
	{
		const FRotator PlayerRotate = GetActorRotation();
		const FVector TargetObjectLocation=TargetObject->GetActorLocation();
		
		const FRotator FindLookAtRotator=UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),FVector(TargetObjectLocation.X,TargetObjectLocation.Y,TargetObjectLocation.Z-200));	
		const FRotator InterpPlayerToTarget=UKismetMathLibrary::RInterpTo(PlayerRotate,FindLookAtRotator,DeltaSeconds,5.0);

		const FRotator LookAtTargetRotator(InterpPlayerToTarget.Pitch,InterpPlayerToTarget.Yaw,PlayerRotate.Roll);
		GetController()->SetControlRotation(LookAtTargetRotator);
	}
}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	APlayerStateBase* PS = GetPlayerState<APlayerStateBase>();
	if(PS)
	{
		AbilitySystemComponent=PS->GetAbilitySystemComponent();
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);
		Attributes = PS->GetAttributes();
		InitializeAttributes();
		GiveDefaultAbilities();
	}

}

void ACharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	APlayerStateBase* PS = GetPlayerState<APlayerStateBase>();
	if(PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);
	}

	InitializeAttributes();
}

void ACharacterBase::InitializeAttributes()
{
	if(AbilitySystemComponent.IsValid())
	{
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);

		for(TSubclassOf<UGameplayEffect> GameplayEffect : DefaultAttributeEffects)
		{
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect,1,EffectContextHandle);

			if(SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());  
			}
		}
	}
}

void ACharacterBase::GiveDefaultAbilities()
{
	if(HasAuthority() && AbilitySystemComponent.IsValid())
	{
		for(TSubclassOf<UGameplayAbility>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(),1,0));
		}
	}
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

URuneAttributeSet* ACharacterBase::GetAttributes() const
{
	return Attributes;
}

UInventoryComponent* ACharacterBase::GetInventoryManagerCompnent() const
{
	return InventoryManagerComponent;
}

AActor* ACharacterBase::GetHitActor_Implementation()
{
	return mHitActor.Get();
}

void ACharacterBase::SetHitActor_Implementation(AActor* HitActor)
{
	mHitActor=HitActor;
}

EHitReaction ACharacterBase::GetHitReaction_Implementation()
{
	return mHitReaction;
}

void ACharacterBase::SetHitReaction_Implementation(EHitReaction HitReaction)
{
	mHitReaction=HitReaction;
}

void ACharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACharacterBase::WeaponCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
												 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
												 const FHitResult& SweepResult)
{
	mHitActor=OtherActor;
	if(Attributes)
	{
		const float Damage = Attributes->GetDamage();
		UGameplayStatics::ApplyDamage(OtherActor,Damage,GetController(),nullptr,nullptr);

		const FVector HitActorForwardVector = OtherActor->GetActorForwardVector();
		const FVector ActorForwardVector = GetActorForwardVector();

		const auto Direction =FVector::DotProduct(HitActorForwardVector,ActorForwardVector);

		if(Direction>=0.0f)
		{
			mHitReaction = EHitReaction::Backward;
		}
		
		else
		{
			mHitReaction= EHitReaction::Forward;
		}
	}
}

void ACharacterBase::ToggleWeaponCollision_Implementation(bool bIsEnable)
{
	if(WeaponCollision->GetCollisionEnabled()==ECollisionEnabled::QueryAndPhysics)
	{
		WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	
}

