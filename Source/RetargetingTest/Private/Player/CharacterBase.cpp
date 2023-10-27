// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/CharacterBase.h"

//engine
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"

//game
#include "AbilitySystemComponent.h"
#include "MotionWarpingComponent.h"
#include "Ability/CustomGameplayAbility.h"
#include "Camera/CameraComponent.h"
#include "Component/CustomSpringArmComponent.h"
#include "Component/WeaponCollisionComponent.h"
#include "Component/InventoryComponent.h"
#include "Component/TargetingComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/PlayerStateBase.h"
#include "RetargetingTest/Public/Component/FloatingCombatTextComponent.h"
#include "Object/BaseWeaponItem.h"
#include "Templates/NonNullPointer.h"
#include "UI/CustomHUD.h"
//////////////////////////////////////////////////////////////////////////
// ARetargetingTestCharacter

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<UCustomSpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, UCustomSpringArmComponent::SocketName);
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

	
	BaseEyeHeight=74.0f;
}

void ACharacterBase::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();
	if(WeaponClass)
	{
		const FActorSpawnParameters SpawnInfo;
		WeaponInstance=GetWorld()->SpawnActor<ABaseWeaponItem>(WeaponClass,GetActorLocation(),GetActorRotation(),SpawnInfo);
	}
	if(WeaponInstance)
	{
		WeaponInstance->SetOwner(this);
		WeaponInstance->OnEquipped(this);
	}

	HUD=Cast<ACustomHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void ACharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CameraBoom->IsCameraLockedToTarget())
	{
		// Vector from player to target
		FVector TargetVect = CameraBoom->CameraTarget->GetComponentLocation() - CameraBoom->GetComponentLocation();
		FRotator TargetRot = TargetVect.GetSafeNormal().Rotation();
		FRotator CurrentRot = GetControlRotation();
		FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaSeconds, LockonControlRotationRate);

		// Update control rotation to face target
		GetController()->SetControlRotation(NewRot);
	}

	if(GetWorld()->TimeSince(InteractionData.LastInteractCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}
}

void ACharacterBase::ToggleWeaponCollision_Implementation(bool IsEnable)
{
	WeaponInstance->GetCollisionComponent()->SetCollisionEnable(IsEnable);
}

UAnimMontage* ACharacterBase::GetHitReaction_Implementation(EHitDirection HitDirection)
{
	switch (HitDirection)
	{
	case EHitDirection::Forward:
		return ForwardHitReaction;
	case EHitDirection::Backward:
		return BackWardHitReaction;
	case EHitDirection::Left:
		return LeftHitReaction;
	case EHitDirection::Right:
		return RightHitReaction;
	default:
		return nullptr;
	}
}

UAnimMontage* ACharacterBase::GetParryMontage_Implementation(EHitDirection HitDirection)
{
	switch (HitDirection)
	{
	case EHitDirection::Up:
		return ParryUp;
	case EHitDirection::Down:
		return ParryDown;
	case EHitDirection::Left:
		return ParryLeft;
	case EHitDirection::Right:
		return ParryRight;
	default:
		return nullptr;
	}
}

bool ACharacterBase::CanReceivedDamaged_Implementation()
{
	UE_LOG(LogTemp,Warning,TEXT("Implementation in BlueprintFunction"));
	return false;
}

void ACharacterBase::SetIFrame_Implementation(bool bEnabled)
{
	bIFrame=bEnabled;
}

void ACharacterBase::PerformInteractionCheck()
{
	InteractionData.LastInteractCheckTime = GetWorld()->GetTimeSeconds();

	FVector TraceStart{GetActorLocation()};
	FVector TraceEnd{TraceStart +(GetActorForwardVector()* InteractionCheckDistance)};

	float LookDirection = FVector::DotProduct(GetActorForwardVector(),GetViewRotation().Vector());

	if(LookDirection>0)
	{
		DrawDebugSphere(GetWorld(), TraceStart, 100.f, 24,FColor::Red, false, 1.0f, 1,2.0f);
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		TArray<FHitResult> TraceHits;
		if(GetWorld()->SweepMultiByChannel(TraceHits,TraceStart,TraceEnd,FQuat::Identity,ECC_Visibility,FCollisionShape::MakeSphere(100.f),QueryParams))
		{
			for(FHitResult TraceHit :TraceHits)
			{
				if(TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
				{
					if(TraceHit.GetActor() != InteractionData.CurrentInteractable)
					{
						FoundInteractable(TraceHit.GetActor());
						return;
					}

					if(TraceHit.GetActor()==InteractionData.CurrentInteractable)
					{
						return;
					}
				}
			}
		}
		NoInteractableFound();
	}
}


void ACharacterBase::FoundInteractable(AActor* NewInteractable)
{
	UE_LOG(LogTemp,Warning,TEXT("FoundInteractable"));
	if(IsInteracting())
	{
		EndInteract();
	}
	
	if(InteractionData.CurrentInteractable)
	{
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();
	}

	InteractionData.CurrentInteractable=NewInteractable;
	TargetInteractable =NewInteractable;

	HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	
	TargetInteractable->BeginFocus();
}

void ACharacterBase::NoInteractableFound()
{
	if(IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}

	if(InteractionData.CurrentInteractable)
	{
		if(IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}
	}

	//interact 위젯을 숨깁니다.
	InteractionData.CurrentInteractable=nullptr;
	TargetInteractable=nullptr;
}

void ACharacterBase::BeginInteract()
{
	PerformInteractionCheck();

	if(InteractionData.CurrentInteractable)
	{
		if(IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->BeginInteraction();

			if(FMath::IsNearlyZero(TargetInteractable->InteractableData.InterfaceDuration,0.1f))
			{
				Interact();
			}
			else
			{
				GetWorldTimerManager().SetTimer(TimerHandle_Interaction,
					this,
					&ACharacterBase::Interact,
					TargetInteractable->InteractableData.InterfaceDuration,
					false);
			}
		}
	}
}

void ACharacterBase::EndInteract()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if(IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteraction();
	}
}

void ACharacterBase::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if(IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact(this);
	}
}

void ACharacterBase::FinishDying()
{
	Destroy();
}

//Server Only
void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	APlayerStateBase* PS = dynamic_cast<APlayerStateBase*>(GetPlayerState());
	if(PS)
	{
		AbilitySystemComponent=(PS->GetAbilitySystemComponent());
		//어빌리티의 OwnerActor와 InAvartActor를 설정해줍니다.
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
		Attributes = PS->GetAttributes();
		InitializeAttributes();
		GiveDefaultAbilities();
	}
}

int32 ACharacterBase::GetAbilityLevel() const
{
	return 1;
}

void ACharacterBase::RemoveCharacterAbilities()
{
	if(!AbilitySystemComponent.IsValid() )
	{
		return;
	}

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	
	for(const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if(Spec.SourceObject == this && DefaultAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}
	
}

//Client Only - 스테이트가 클라이언트에 존재하게 됩니다.
void ACharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	APlayerStateBase* PS = GetPlayerState<APlayerStateBase>();
	if(PS)
	{
		Attributes = PS->GetAttributes();
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
		for(TSubclassOf<UCustomGameplayAbility>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(),1,static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID),this));
		}
	}
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

UBaseAttributeSet* ACharacterBase::GetAttributes() const
{
	
	return Attributes;
	
}

UInventoryComponent* ACharacterBase::GetInventoryManagerComponent() const
{
	return InventoryManagerComponent;
}

void ACharacterBase::SetWeaponInstance(ABaseWeaponItem* NewWeaponInstance)
{
	WeaponInstance=NewWeaponInstance;
}

E4WAYParryDirection ACharacterBase::GetParryHitDirection() const
{
	return ParryHitDirection;
}

void ACharacterBase::Die()
{
	RemoveCharacterAbilities();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale=0;
	GetCharacterMovement()->Velocity=FVector(0);

	if(AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAbilities();
		
	}
}

void ACharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}



