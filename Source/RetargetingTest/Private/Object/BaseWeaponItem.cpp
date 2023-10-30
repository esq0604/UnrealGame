// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BaseWeaponItem.h"

#include "Component/WeaponCollisionComponent.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"
#include "Weapon/GameplayAbility_MeleeWeapon.h"
#include "Ability/CustomGameplayAbility.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Attribute/BaseAttributeSet.h"

#include "Data/CustomAbilitySet.h"


// Sets default values
ABaseWeaponItem::ABaseWeaponItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	WeaponCollisionComp=CreateDefaultSubobject<UWeaponCollisionComponent>(TEXT("WeaponCollisionComp"));
	WeaponCollisionComp->OnHitDelegate.BindUObject(this,&ABaseWeaponItem::OnHitDelegateFunction);
	
	//AbilitySystemComponent=CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
}

UAbilitySystemComponent* ABaseWeaponItem::GetAbilitySystemComponent() const
{
	return 	UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
;
}

void ABaseWeaponItem::RemoveAbilities()
{
	for(FGameplayAbilitySpecHandle SpecHandle : AbilitySpecHandles)
	{
		GetAbilitySystemComponent()->ClearAbility(SpecHandle);
	}
}

/**
 * @brief 장착 및 ItemData에 있는 AbilitySet를 Character에게 적용시킵니다.
 * @param Character 아이템을 장착할 Character입니다.
 * @param InItemData 장착시 적용할 ItemData입니다.
 */
void ABaseWeaponItem::Equip(ACharacter* Character,UItemDataAsset* InItemData)
{
	Super::Equip(Character,InItemData);
	const UEquipmentDataAsset* EquipData = dynamic_cast<UEquipmentDataAsset*>(InItemData);

	if(GetOwner()!=nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("GetOwner :%s"),*GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("GetOwner nullptr"));

	}
	for(TObjectPtr<const UCustomAbilitySet> AbilitySet : EquipData->AbilitySetToEquip)
	{
		for(int Index=0; Index < AbilitySet->EquippedGameplayAbilities.Num(); Index++)
		{
			const FAbilitySet_GameplayAbility& AbilityToGrant = AbilitySet->EquippedGameplayAbilities[Index];

			UCustomGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UCustomGameplayAbility>();	
			FGameplayAbilitySpec AbilitySpec(AbilityCDO,1,static_cast<int32>(AbilityCDO->AbilityInputID),this);
			AbilitySpecHandles.Add(GetAbilitySystemComponent()->GiveAbility(AbilitySpec));
		}
	}

	ACharacterBase* CharacterBase = dynamic_cast<ACharacterBase*>(Character);
	CharacterBase->SetWeaponInstance(this);
}

void ABaseWeaponItem::UnEquip(ACharacter* Character)
{
	Super::UnEquip(Character);

	RemoveAbilities();
	const ACharacterBase* CharacterBase = dynamic_cast<ACharacterBase*>(Character);
	if(CharacterBase!=nullptr)
	{
		FGameplayAttributeData DamageAttribute = CharacterBase->GetAttributes()->Damage;
		DamageAttribute.SetCurrentValue(DamageAttribute.GetCurrentValue());
	}
	Destroy();

}

// Called when the game starts or when spawned
void ABaseWeaponItem::BeginPlay()
{
	Super::BeginPlay();

	if(WeaponData)
	{
		WeaponCollisionComp->SetCollisionMeshComp(StaticMeshComponent);
	}
}

void ABaseWeaponItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

/**
 * WeaponCollisionComp에서 OnHit 델리게이트에 의해 호출됩니다. 게임플레이어빌리티에 이벤트를 넘겨주고 Payload데이터로 히트된 타겟을 넘겨줍니다.
 * @param EventData : Payload Data입니다.
 * @param HitResult : EffectContext에 넣어줄 HitReulst입니다. GameplayCue에서 타겟과 소스액터의 방향을 구하기 위해 사용합니다.
 */
void ABaseWeaponItem::OnHitDelegateFunction(FGameplayEventData EventData,const FHitResult HitResult)
{
	TArray<FGameplayAbilitySpec*> StoreSpec;

	for(const FGameplayAbilitySpecHandle SpecHandle : AbilitySpecHandles)
	{
		const FGameplayAbilitySpec* Spec = GetAbilitySystemComponent()->FindAbilitySpecFromHandle(SpecHandle);
		//어빌리티가 공격어빌리티 태그를 가지고있다면 GameplayEffect를 적용시키기 위한 정보를 담아서 GameplayEventData로 넘겨주게됩니다. 
		 if(Spec->Ability->AbilityTags.HasTag(AttackAbilityTag))
		 {
			if(Spec->IsActive())
			{
				FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
				EffectContextHandle.AddHitResult(HitResult);
				EffectContextHandle.AddInstigator(GetOwner(),GetOwner());
				EventData.ContextHandle=EffectContextHandle;
				EventData.Instigator=GetOwner();
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(),FGameplayTag::RequestGameplayTag("Ability.Attack.Melee"),EventData);
				return;
			}
		}
	}
}

// /**
//  * 플레이어가 상호작용시 호출됩니다.
//  */
// void ABaseWeaponInstance::Interact_Implementation()
// {
// 	//const TSubclassOf<UInventoryComponent> InvenCompClass = UInventoryComponent::StaticClass();
// 	
// 	UActorComponent* Comp=GetOwner()->GetComponentByClass(UInventoryComponent::StaticClass());
// 	if(Comp)
// 	{
// 		UInventoryComponent* InvenComp = dynamic_cast<UInventoryComponent*>(Comp);
// 		if(InvenComp)
// 		{
// 			InvenComp->AddItemToInventory(this);
// 			WeaponStaticMeshComponent->SetVisibility(false);
// 			WeaponStaticMeshComponent->SetSimulatePhysics(false);
// 			WeaponStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
// 			OffDetecte();
// 		}	
// 	}
// }

/**
 * 인벤토리에 있는 아이템을 클릭시 호출되는 함수입니다.
 * @param  Character : 호출한 대상을 인자로 받습니다.
 */

	// Character->SetWeaponInstance(this);
	//
	// if(!bIsEquipped)
	// {
	// 	OnEquipped(Character);
	// }
	// else
	// {
	// 	OffEquipped(Character);
	// }

