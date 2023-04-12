  // Copyright Epic Games, Inc. All Rights Reserved.

#include "RetargetingTest/Player/Public/CharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "RetargetingTest/Component/Public/BasePlayerStatComponent.h"
#include "RetargetingTest/Player/Public/CharaterAnimInstance.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Engine/EngineTypes.h"
#include "RetargetingTest/Component/Public/FloatingCombatTextComponent.h"
#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"
#include "RetargetingTest/UI/Public/PlayerGauge.h"
#include "GameplayTagContainer.h"
#include "RetargetingTest/Object/Public/BaseStateObject.h"
#include "RetargetingTest/Object/Public/ItemBase.h"
#include "RetargetingTest/UI/Public/Inventory.h"
#include "RetargetingTest/UI/Public/PlayerHUD.h"
#include "RetargetingTest/UI/Public/QuickSlot.h"
#include "RetargetingTest/UI/Public/Slot.h"
#include "MotionWarpingComponent.h"
#include "RetargetingTest/Component/Public/BaseAbilityManagerComponent.h"
#include "RetargetingTest/Controller/public/MyPlayerController.h"
#include "RetargetingTest/Weapon/public/BaseWeapon.h"
  //////////////////////////////////////////////////////////////////////////
// ARetargetingTestCharacter

ACharacterBase::ACharacterBase()
	:AttackRange(200.0f) , AttackRadius(50.0f),MaxCombo(4),IsAttacking(false)
{
	PrimaryActorTick.bCanEverTick=true;
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
	
	MotionWarpComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpComponent"));
	AbilityManagerComponent= CreateDefaultSubobject<UBaseAbilityManagerComponent>(TEXT("AbilityManagerComponent"));

	//DefaultWeaponToSpawn=CreateDefaultSubobject<ABaseWeapon>(TEXT("DefaultWeapon"));
}
/**
 * 데미지 전달을 위한 함수입니다. 현재 상태가 Dodge State가 아니라면 데미지를 받습니다.
 * @param DamageAmount - 받는 데미지의 양 입니다.
 *
 */
float ACharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
                                            AController* EventInstigator, AActor* DamageCauser)
{
	
	if(bCanDamaged)
	{
	    UE_LOG(LogTemp,Warning,TEXT("Player Get Damage"));
		StatComponent->SufferDamage(DamageAmount);
	
		return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}
	 return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

}

/**
 * 플레이어가 공격을 할 시 범위를 확인하기 위해 호출됩니다.
 * @warning  플레이어애님인스턴스의 몽타주애님 노티파이 델리게이트에 바인딩되어 있습니다.
 */
void ACharacterBase::AttackCheck()
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
		    UE_LOG(LogTemp,Warning,TEXT("Player Attack Result Monster"));
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
 * Default Weapon을 생성하고, 초기화합니다.
 * PlayerController를 초기화합니다.
 */
void ACharacterBase::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();
	DefaultWeaponToSpawn=NewObject<ABaseWeapon>(this,DefaultWeaponToSpawnClass);
	DefaultWeaponToSpawn->CreateWeaponStateAndAbility();
	
	if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(Controller))
	{
		PlayerController->Init();
		PlayerHUD = CreateWidget<UPlayerHUD>(PlayerController, PlayerHUDClass);
		if(PlayerHUD != nullptr)
		{
			PlayerHUD->SetCharacter(this);
			PlayerHUD->Init();
			PlayerHUD->AddToViewport();
		}
	}
}

/**
 * 현재 속도가 0이면 Idle 상태로 전환합니다. 
 */
void ACharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

/**
 * Sprint입력이 끝날때 호출되는 함수입니다. EndState를 통해 다른 상태로 바뀔 수 있습니다.
 */
void ACharacterBase::SprintEnd()
{

}

/**
 *	TODO: 게임의 플레이어 HUD관련부분은 게임모드클래스에서 관리해야합니다. 
 *	인벤토리 토글 입력에 대한 매핑 함수 입니다. I키를 통해 인벤토리를 열고 닫습니다.
 */
void ACharacterBase::ToggleInventory()
{
	if(PlayerHUD!=nullptr)
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
	if(CurrentInteractable!=nullptr)
	{
		CurrentInteractable->Interact_Implementation();
		if(PlayerHUD->GetInventory()!=nullptr)
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
	FVector EndTrace = GetActorLocation()+GetActorForwardVector()*200.0f;

	FHitResult HitResult;

	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(HitResult,StartTrace,EndTrace,ECC_WorldDynamic,CQP);

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
	if(PotentialInteractable ==nullptr)
	{
		CurrentInteractable=nullptr;
		return;
	}
	else
	{
		CurrentInteractable=PotentialInteractable;
	}
}

/**
 * QuickSlot은 1,2,3,4번순으로 슬롯이 지정되어 있어. num을 넘겨줘 해당 슬롯을 사용하도록합니다
 *
 */
void ACharacterBase::UseQuickSlot(int UsedSlotIdx)
{
	PlayerHUD->GetQuickSlot()->Use(UsedSlotIdx-1);
}

/**
 * @param Item - 인벤토리에 들어갈 아이템이 들어옵니다.
 */
bool ACharacterBase::AddItemToInventory(AItemBase* Item)
{
	if(Item!=nullptr)
	{
		const int32 AvaliableSlot = Inventory.Find(nullptr);
		if(AvaliableSlot!= INDEX_NONE)
		{
			Inventory[AvaliableSlot]=Item;
			return true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("You cant carry any more items"));
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

/**
 * 캐릭터의 IA_Sprint 와 바인딩된 함수입니다. SprintState로 진입합니다.
 * 해당 로직의 문제점은 SprintState로 진입할 수 없을때에도 스태미나를 사용하는것 입니다.
 * 이를 올바르게 처리하기 위해선 Sprint State에서 로직을 처리하는것 입니다.
 */


UBasePlayerStatComponent* ACharacterBase::GetStatComponent() const
{
	return StatComponent;
}


/**
 * 슬롯에 있는 아이템의 썸네일을 반환합니다.
 * @param Slot - 인벤토리 슬롯의 인덱스가 들어옵니다.
 */
UTexture2D* ACharacterBase::GetThumnailAtInventorySlot(int32 Slot) const
{
	if(Inventory[Slot]!=nullptr)
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
	if(Inventory[Slot]!=nullptr)
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
	if(Inventory[Slot] != nullptr && Slot!= -1)
	{
		TArray<USlot*> TempSlot;
		
		Inventory[Slot]->UseItem(this);
		
		//레퍼런스 슬롯이 없다면 인벤토리만 갱신합니다.
		if(Inventory[Slot]->ReferenceSlot.IsEmpty())
		{
			if(Inventory[Slot]->GetCount()==0)
			{
				Inventory[Slot]=nullptr;
			}
			PlayerHUD->GetInventory()->GetSlot(Slot)->Refresh();
		}
		//있다면 레퍼런스 슬롯을 옮겨줍니다.
		else
		{
			for(USlot* eachSlot : Inventory[Slot]->ReferenceSlot)
			{
				TempSlot.Add(eachSlot);
			}
			if(Inventory[Slot]->GetCount()==0)
			{
				Inventory[Slot]=nullptr;
			}
			for(USlot* eachSlot : TempSlot)
			{
				if(eachSlot!=nullptr)
				{
					eachSlot->Refresh();
				}
			}
			PlayerHUD->GetInventory()->Refresh();
		}
	}
}

void ACharacterBase::Attack(const FInputActionValue& Value)
{
	if(IsAttacking)
	{
		if(CanNextCombo)
		{
			IsComboInputOn=true;
		}
	}
	else
	{
		//PlayerStateManagerComponent->SetCurrentActiveState(PlayerStateManagerComponent->GetStateOfGameplayTag(FGameplayTag::RequestGameplayTag("State.Walk")));
		//if(PlayerStateManagerComponent->GetCurrentActiveState()->GetGameplayTag()==FGameplayTag::RequestGameplayTag("State.Attack"))
		{
			AttackStartComboState();
			mAnimInstance->PlayAttackMontage();
			IsAttacking=true;
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
	mAnimInstance = Cast<UCharaterAnimInstance>(GetMesh()->GetAnimInstance());
	if(mAnimInstance != nullptr)
	{
		mAnimInstance->OnAttackHitCheck.AddUObject(this,&ACharacterBase::AttackCheck);
		mAnimInstance->OnMontageEnded.AddDynamic(this,&ACharacterBase::OnAttackMontageEnded);
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
void ACharacterBase::AttackStartComboState()
{
	CanNextCombo=true;
	IsComboInputOn=false;
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo+1,1,MaxCombo);
}

/**
 * 몽타주가 끝나면 콤보공격에 대한 상태들을 초기화합니다.
 */
void ACharacterBase::AttackEndComboState()
{
	CanNextCombo=false;
	IsComboInputOn=false;
	CurrentCombo=0;
}

/**
 * 몽타주가 끝나면 콤보공격에 대한 상태들을 초기화합니다.
 */
void ACharacterBase::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking=false;
	AttackEndComboState();
	
}

/**
 * Space키에 매핑된 함수입니다. Walk 상태라면 Dodge를, Sprint 상태라면 점프를 수행합니다.
 * 현재 Dodge 입력 매핑은 Blueprint로 되어있습니다.
 */
void ACharacterBase::JumpAndDodge()
{

}



