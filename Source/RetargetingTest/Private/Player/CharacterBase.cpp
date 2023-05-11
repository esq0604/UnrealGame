// Copyright Epic Games, Inc. All Rights Reserved.

#include "RetargetingTest/Public/Player/CharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Engine/EngineTypes.h"
#include "MotionWarpingComponent.h"

#include "AbilitySystemComponent.h"
#include "Component/InventoryComponent.h"
#include "RetargetingTest/Public/Attribute/RuneAttributeSet.h"
#include "RetargetingTest/Public/Component/FloatingCombatTextComponent.h"
#include "RetargetingTest/Public/Object/ItemBase.h"
#include "RetargetingTest/Public/Player/CharaterAnimInstance.h"
#include "RetargetingTest/Public/UI/Inventory.h"
#include "RetargetingTest/Public/UI/PlayerHUD.h"
#include "RetargetingTest/Public/UI/QuickSlot.h"
#include "RetargetingTest/Public/UI/Slot.h"
//////////////////////////////////////////////////////////////////////////
// ARetargetingTestCharacter

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
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
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	//사용자 정의 컴포넌트입니다.
	FloatingTextComponent = CreateDefaultSubobject<UFloatingCombatTextComponent>(TEXT("FloatingDamageComponent"));

	MotionWarpComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpComponent"));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<URuneAttributeSet>(TEXT("Attribute"));

	InventoryComponent=CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

/**
 * 게임플레이의 시작 전 초기화 단계입니다.
 * 플레이어의 HP Widget Component의 초기화 후에 뷰포트에 노출해야 하기 때문에 BeginPlay에 작성하였습니다.
 * Default Weapon을 생성하고, 초기화합니다.
 * PlayerController를 초기화합니다.
 */
void ACharacterBase::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();
	// if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(Controller))
	// {
	// 	PlayerController->Init();
	// 	PlayerHUD = CreateWidget<UPlayerHUD>(PlayerController, PlayerHUDClass);
	// 	if (PlayerHUD != nullptr)
	// 	{
	// 		PlayerHUD->SetCharacter(this);
	// 		PlayerHUD->Init();
	// 		PlayerHUD->AddToViewport();
	// 	}
	// }
	
}

/**
 * 현재 속도가 0이면 Idle 상태로 전환합니다. 
 */
void ACharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

/**
 *	TODO: 게임의 플레이어 HUD관련부분은 게임모드클래스에서 관리해야합니다. 
 *	인벤토리 토글 입력에 대한 매핑 함수 입니다. I키를 통해 인벤토리를 열고 닫습니다.
 */
void ACharacterBase::ToggleInventory()
{
	if (PlayerHUD != nullptr)
	{
		PlayerHUD->ToggleInventory();
	}
}

/**
 *	TODO : 매번 전체 인벤토리를 Referesh하는건 비효율적입니다.
 *	현재 인터랙터블이 있는 경우 인터랙터블과 상호작용합니다.
 */
void ACharacterBase::Interact()
{
	CheckForInteractalbe();
	if (CurrentInteractable != nullptr)
	{
		CurrentInteractable->Interact_Implementation();
		if (PlayerHUD->GetInventory() != nullptr)
		{
			PlayerHUD->GetInventory()->Refresh();
		}
	}
}

/**
 * 라인트레이스를 이용해 인터렉터블 아이템이 있는지 확인합니다.
 * 
 */
void ACharacterBase::CheckForInteractalbe()
{
	FVector StartTrace = GetActorLocation();
	FVector EndTrace = GetActorLocation() + GetActorForwardVector() * 200.0f;

	FHitResult HitResult;

	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_WorldDynamic, CQP);

	AItemBase* PotentialInteractable = Cast<AItemBase>(HitResult.GetActor());

	DrawDebugLine(GetWorld(),
	              StartTrace,
	              EndTrace,
	              FColor::Red,
	              true,
	              1,
	              0,
	              2
	);
	if (PotentialInteractable == nullptr)
	{
		CurrentInteractable = nullptr;
		return;
	}
	else
	{
		CurrentInteractable = PotentialInteractable;
	}
}

/**
 * QuickSlot은 1,2,3,4번순으로 슬롯이 지정되어 있어. num을 넘겨줘 해당 슬롯을 사용하도록합니다
 *
 */
void ACharacterBase::UseQuickSlot(int UsedSlotIdx)
{
	PlayerHUD->GetQuickSlot()->Use(UsedSlotIdx - 1);
}

/**
 * @param Item - 인벤토리에 들어갈 아이템이 들어옵니다.
 */
bool ACharacterBase::AddItemToInventory(AItemBase* Item)
{
	if (Item != nullptr)
	{
		const int32 AvaliableSlot = Inventory.Find(nullptr);
		if (AvaliableSlot != INDEX_NONE)
		{
			Inventory[AvaliableSlot] = Item;
			return true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,TEXT("You cant carry any more items"));
		}
	}
	return false;
}

AItemBase* ACharacterBase::GetItemAtInventory(int32 Index)
{
	return Inventory[Index];
}

TArray<AItemBase*> ACharacterBase::GetInventory() const
{
	return Inventory;
}

ABaseWeapon* ACharacterBase::GetEquipedWeapon() const
{
	return EquipedWeapon;
}


/**
* 슬롯에 있는 아이템의 썸네일을 반환합니다.
* @param Slot - 인벤토리 슬롯의 인덱스가 들어옵니다.
*/
UTexture2D* ACharacterBase::GetThumnailAtInventorySlot(int32 Slot) const
{
	if (Inventory[Slot] != nullptr)
	{
		return Inventory[Slot]->PickupThumbnail;
	}
	return nullptr;
}

/**
 * 슬롯에 있는 아이템의 이름을 반환합니다.
 * @param Slot - 인벤토리 슬롯의 인덱스가 들어옵니다.
 */
FString ACharacterBase::GetItemNameAtInventorySlot(int32 Slot) const
{
	if (Inventory[Slot] != nullptr)
	{
		return Inventory[Slot]->ItemName;
	}
	return FString("None");
}

/**
 * TODO: 인벤토리의 UsealbeItem이 여러개일 경우를 생각해야합니다, 아이템을 사용시마다 인벤토리 전체를 초기화 하는건 비효율적입니다.
 * 아이템의 레퍼런스 슬롯을 받아 저장한 뒤, 사용 후 슬롯을 갱신합니다. 이때 인벤토리는 레퍼런스 슬롯에 들어가있지 않기때문에 인벤토리도 갱신합니다.
 * @param Slot - 인벤토리 슬롯의 인덱스가 들어옵니다.
 */
void ACharacterBase::UseItemAtInventorySlot(int32 Slot)
{
	if (Inventory[Slot] != nullptr && Slot != -1)
	{
		TArray<USlot*> TempSlot;

		Inventory[Slot]->UseItem(this);

		//레퍼런스 슬롯이 없다면 인벤토리만 갱신합니다.
		if (Inventory[Slot]->ReferenceSlot.IsEmpty())
		{
			if (Inventory[Slot]->GetCount() == 0)
			{
				Inventory[Slot] = nullptr;
			}
			PlayerHUD->GetInventory()->GetSlot(Slot)->Refresh();
		}
		//있다면 레퍼런스 슬롯을 옮겨줍니다.
		else
		{
			for (USlot* eachSlot : Inventory[Slot]->ReferenceSlot)
			{
				TempSlot.Add(eachSlot);
			}
			if (Inventory[Slot]->GetCount() == 0)
			{
				Inventory[Slot] = nullptr;
			}
			for (USlot* eachSlot : TempSlot)
			{
				if (eachSlot != nullptr)
				{
					eachSlot->Refresh();
				}
			}
			PlayerHUD->GetInventory()->Refresh();
		}
	}
}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
	}

	InitializeAttributes();
	GiveDefaultAbilities();
}

void ACharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
	}

	InitializeAttributes();
}

void ACharacterBase::InitializeAttributes()
{
	if(AbilitySystemComponent&&DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect,1,EffectContextHandle);

		if(SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());  
		}
	}
}

void ACharacterBase::GiveDefaultAbilities()
{
	if(HasAuthority() && AbilitySystemComponent)
	{
		for(TSubclassOf<UGameplayAbility>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(),1,0));
		}
	}
}

/**
 * 캐릭터가 보유한 컴포넌트들의 초기화 시점입니다.애님인스턴스에서 선언한 델리게이트들을 바인딩합니다.
 * 델리게이트에 Lamda를 사용해 다음 공격에 대한 노티파이가 발생한다면 콤보공격을 시작하도록 합니다.
 */
void ACharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}
