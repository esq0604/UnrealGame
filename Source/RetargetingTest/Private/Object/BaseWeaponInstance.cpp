// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BaseWeaponInstance.h"
#include "Component/WeaponCollisionComponent.h"
#include "RetargetingTest/Public/Controller/MyPlayerController.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"
#include "Weapon/GameplayAbility_MeleeWeapon.h"
#include "Ability/CustomGameplayAbility.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Attribute/BaseAttributeSet.h"
#include "Component/InventoryComponent.h"


// Sets default values
ABaseWeaponInstance::ABaseWeaponInstance()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	WeaponStaticMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponCollisionComp=CreateDefaultSubobject<UWeaponCollisionComponent>(TEXT("WeaponCollisionComp"));
	WeaponCollisionComp->OnHitDelegate.BindUObject(this,&ABaseWeaponInstance::OnHitDelegateFunction);


	AbilitySystemComponent=CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));

	SetRootComponent(WeaponStaticMeshComponent);
	EquipItemType=EEquipment_Type::Weapon;
}

UAbilitySystemComponent* ABaseWeaponInstance::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

/**
 * 무기가 가지고 있는 어빌리티 클래스들을 Owner에게 적용시킵니다.
 */
void ABaseWeaponInstance::AddAbilities()
{
	AbilitySystemComponent=UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());

	if(Abilities.Num()>0)
	{
		for (TSubclassOf<UCustomGameplayAbility>& Ability : Abilities)
		{
			AbilitySpecHandles.Add(AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(),1,static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID),this)));
		}
	}
	
}

void ABaseWeaponInstance::RemoveAbilities()
{
	for(FGameplayAbilitySpecHandle SpecHandle : AbilitySpecHandles)
	{
		AbilitySystemComponent->ClearAbility(SpecHandle);
	}
}

void ABaseWeaponInstance::OnEquipped(ACharacter* Character)
{
	AddAbilities();
	WeaponStaticMeshComponent->SetVisibility(true);
	WeaponStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if(Character)
	{
		AttachToComponent(Character->GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,AttachSocketName);
		bIsEquipped=true;
		
		const ACharacterBase* CharacterBase = dynamic_cast<ACharacterBase*>(Character);
		if(CharacterBase!=nullptr)
		{
			FGameplayAttributeData DamageAttribute = CharacterBase->GetAttributes()->Damage;
			DamageAttribute.SetCurrentValue(DamageAttribute.GetCurrentValue()+Stats.ATK);
			UE_LOG(LogTemp,Warning,TEXT("Current Damage : %f"),DamageAttribute.GetCurrentValue());
		}
		
	}
	
}

void ABaseWeaponInstance::OffEquipped(ACharacter* Character)
{
	RemoveAbilities();
	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	WeaponStaticMeshComponent->SetVisibility(false);
	bIsEquipped=false;

	
	const ACharacterBase* CharacterBase = dynamic_cast<ACharacterBase*>(Character);
	if(CharacterBase!=nullptr)
	{
		FGameplayAttributeData DamageAttribute = CharacterBase->GetAttributes()->Damage;
		DamageAttribute.SetCurrentValue(DamageAttribute.GetCurrentValue());

		UE_LOG(LogTemp,Warning,TEXT("Current Damage : %f"),DamageAttribute.GetCurrentValue());
	}
}

FName ABaseWeaponInstance::GetWeaponTraceStartSocketName() const
{
	return WeaponTraceStartSocketName;
}

FName ABaseWeaponInstance::GetWeaponTraceEndSocketName() const
{
	return WeaponTraceEndSocketName;
}

UWeaponCollisionComponent* ABaseWeaponInstance::GetCollisionComponent() const
{
	return WeaponCollisionComp;
}

// Called when the game starts or when spawned
void ABaseWeaponInstance::BeginPlay()
{
	Super::BeginPlay();
	WeaponStaticMeshComponent->SetStaticMesh(WeaponStaticMesh);
	WeaponCollisionComp->SetCollisionMeshComp(WeaponStaticMeshComponent);
}

void ABaseWeaponInstance::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

/**
 * WeaponCollisionComp에서 OnHit 델리게이트에 의해 호출됩니다. 게임플레이어빌리티에 이벤트를 넘겨주고 Payload데이터로 히트된 타겟을 넘겨줍니다.
 * @param EventData : Payload Data입니다.
 * @param HitResult : EffectContext에 넣어줄 HitReulst입니다. GameplayCue에서 타겟과 소스액터의 방향을 구하기 위해 사용합니다.
 */
void ABaseWeaponInstance::OnHitDelegateFunction(FGameplayEventData EventData,const FHitResult HitResult)
{
	TArray<FGameplayAbilitySpec*> StoreSpec;

	for(const FGameplayAbilitySpecHandle SpecHandle : AbilitySpecHandles)
	{
		const FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle);

		//어빌리티가 공격어빌리티 태그를 가지고있다면 GameplayEffect를 적용시키기 위한 정보를 담아서 GameplayEventData로 넘겨주게됩니다. 
		// if(Spec->Ability->AbilityTags==AttackAbilityTagContainer.HasTag())
		// {
			if(Spec->IsActive())
			{
				FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
				EffectContextHandle.AddHitResult(HitResult);
				EffectContextHandle.AddInstigator(GetOwner(),GetOwner());
				EventData.ContextHandle=EffectContextHandle;
				EventData.Instigator=GetOwner();
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(),FGameplayTag::RequestGameplayTag("Ability.Attack.Melee"),EventData);
				return;
			}
		//}
	}
}

/**
 * 플레이어가 상호작용시 호출됩니다.
 */
void ABaseWeaponInstance::Interact_Implementation()
{
	//const TSubclassOf<UInventoryComponent> InvenCompClass = UInventoryComponent::StaticClass();
	
	UActorComponent* Comp=GetOwner()->GetComponentByClass(UInventoryComponent::StaticClass());
	if(Comp)
	{
		UInventoryComponent* InvenComp = dynamic_cast<UInventoryComponent*>(Comp);
		if(InvenComp)
		{
			InvenComp->AddItemToInventory(this);
			WeaponStaticMeshComponent->SetVisibility(false);
			WeaponStaticMeshComponent->SetSimulatePhysics(false);
			WeaponStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			OffDetecte();
		}	
	}
}

/**
 * 인벤토리에 있는 아이템을 클릭시 호출되는 함수입니다.
 * @param  Character : 호출한 대상을 인자로 받습니다.
 */
void ABaseWeaponInstance::UseItem_Implementation(ACharacterBase* Character)
{
	Character->SetWeaponInstance(this);

	if(!bIsEquipped)
	{
		OnEquipped(Character);
	}
	else
	{
		OffEquipped(Character);
	}
}
