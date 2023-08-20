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
#include "Ability/CharacterAbilitySystemComponent.h"
#include "Ability/CustomAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Component/WeaponCollisionComponent.h"
#include "Component/InventoryComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/PlayerStateBase.h"
#include "RetargetingTest/Public/Component/FloatingCombatTextComponent.h"
#include "Player/CharaterAnimInstance.h"
#include "RetargetingTest/RetargetingTest.h"
#include "Weapon/BaseWeaponInstance.h"
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
	//WeaponInstance = CreateDefaultSubobject<ABaseWeaponInstance>(TEXT("Weapon"));
	//TargetingComponent=CreateDefaultSubobject<UTargetingComponent>("TargetingComponent");
}

void ACharacterBase::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("C++ BeginPlay"));
	FActorSpawnParameters SpawnInfo;
	WeaponInstance=GetWorld()->SpawnActor<ABaseWeaponInstance>(WeaponClass,GetActorLocation(),GetActorRotation(),SpawnInfo);
	
	if(WeaponInstance!=nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("Weapon Instance is valid"));
		WeaponInstance->SetOwner(this);
		WeaponInstance->AddAbilities();
		WeaponInstance->OnEquipped();
	}
	if(!Attributes)
	{
		UE_LOG(LogTemp,Warning,TEXT("Player Attributes is not valid"));
	}
}

void ACharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void ACharacterBase::ToggleWeaponCollision_Implementation(bool IsEnable)
{
	WeaponInstance->GetCollisionComponent().Get()->SetCollisionEnable(IsEnable);
}

void ACharacterBase::FinishDying()
{
	Destroy();
}

// void ACharacterBase::BindASCInput()
// {
// 	FTopLevelAssetPath AbilityEnumAssetPath = FTopLevelAssetPath(FName("/Script/RetargetingTest"), FName("CustomAbilityID"));
// 	AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
// 	FString("CancelTarget"), AbilityEnumAssetPath, static_cast<int32>(CustomAbilityID::Confirm), static_cast<int32>(CustomAbilityID::Cancel)));
// 	//AbilitySystemComponent->AbilityLocalInputPressed()
// }

//Server Only
void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	APlayerStateBase* PS = GetPlayerState<APlayerStateBase>();
	if(PS)
	{
		AbilitySystemComponent=Cast<UCharacterAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		//어빌리티의 OwnerActor와 InAvartActor를 설정해줍니다.
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);
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
	if(!AbilitySystemComponent.IsValid() || !AbilitySystemComponent->CharacterAbilitiesGiven)
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
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);
	}
	//BindASCInput();

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
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(),1,0,this));
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

UInventoryComponent* ACharacterBase::GetInventoryManagerCompnent() const
{
	return InventoryManagerComponent;
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

void ACharacterBase::AttackWithMotionWarp()
{
const FVector MovementInputVector = GetLastMovementInputVector();
if (MovementInputVector.IsZero())
{
	MotionWarpComponent->RemoveWarpTarget(TEXT("Warp"));
	return;
}

const FVector PlayerLoc = GetActorLocation();
const FVector ForwardDist = GetActorForwardVector() *100.f;
const FVector TargetLoc = (MovementInputVector.GetSafeNormal() * ForwardDist) + PlayerLoc;
const FRotator TargetRotator = UKismetMathLibrary::MakeRotFromX(MovementInputVector);

MotionWarpComponent->AddOrUpdateWarpTargetFromLocationAndRotation(TEXT("Warp"), TargetLoc, TargetRotator);
}

void ACharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}



