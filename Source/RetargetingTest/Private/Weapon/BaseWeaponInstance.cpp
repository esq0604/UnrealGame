// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Weapon/BaseWeaponInstance.h"

#include "Ability/CharacterGameplayAbility.h"
#include "Component/WeaponCollisionComponent.h"
#include "RetargetingTest/Public/Controller/MyPlayerController.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"
#include "Weapon/GameplayAbility_MeleeWeapon.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"


// Sets default values
ABaseWeaponInstance::ABaseWeaponInstance()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	WeaponStaticMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	CollisionComp=CreateDefaultSubobject<UWeaponCollisionComponent>(TEXT("CollisionComp"));
	AbilitySystemComponent=CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
}

UAbilitySystemComponent* ABaseWeaponInstance::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseWeaponInstance::AddAbilities()
{
	check(AbilitySystemComponent)
	
	for (TSubclassOf<UGameplayAbility>& Ability : Abilities)
	{
		 AbilitySpecHandles.Add(AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(),1,0,this)));
	}

	for(const FGameplayAbilitySpecHandle SpecHandle : AbilitySpecHandles)
	{
		const FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle);
		AbilityInstances.Add((Spec->Ability));
	}
}

void ABaseWeaponInstance::RemoveAbilities()
{
	for(FGameplayAbilitySpecHandle SpecHandle : AbilitySpecHandles)
	{
		AbilitySystemComponent->ClearAbility(SpecHandle);
	}
}

void ABaseWeaponInstance::SetOwningCharacter(ACharacterBase* InOwningCharacter)
{
	OwningCharacter = InOwningCharacter;
	SetOwner(InOwningCharacter);
	AbilitySystemComponent=InOwningCharacter->GetAbilitySystemComponent();
}

void ABaseWeaponInstance::OnEquipped()
{
	const ACharacter* character = Cast<ACharacter>(GetOwner());
	
	AttachToComponent(character->GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,AttachSocketName);
}

FName ABaseWeaponInstance::GetWeaponTraceStartSocketName() const
{
	return WeaponTraceStartSocketName;
}

FName ABaseWeaponInstance::GetWeaponTraceEndSocketName() const
{
	return WeaponTraceEndSocketName;
}

TWeakObjectPtr<UWeaponCollisionComponent> ABaseWeaponInstance::GetCollisionComponent() const
{
	return CollisionComp;
}

// Called when the game starts or when spawned
void ABaseWeaponInstance::BeginPlay()
{
	Super::BeginPlay();
	WeaponStaticMeshComponent->SetStaticMesh(WeaponStaticMesh);
	CollisionComp->SetCollisionMeshComp(WeaponStaticMeshComponent);
}

void ABaseWeaponInstance::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CollisionComp->OnHitDelegate.BindUObject(this,&ABaseWeaponInstance::OnHitDelegateFunction);
}

/**
 * WeaponCollisionComp에서 OnHit 델리게이트에 의해 호출됩니다. 게임플레이어빌리티에 이벤트를 넘겨주고 Payload데이터로 히트된 타겟을 넘겨줍니다.
 * @param EventData : Payload Data입니다.
 * @param HitResult : EffectContext에 넣어줄 HitReulst입니다. GameplayCue에서 타겟과 소스액터의 방향을 구하기 위해 사용합니다.
 */
void ABaseWeaponInstance::OnHitDelegateFunction(const FGameplayEventData& EventData,const FHitResult& HitResult)
{
	TArray<FGameplayAbilitySpec*> StoreSpec;

	for(const FGameplayAbilitySpecHandle SpecHandle : AbilitySpecHandles)
	{
		const FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle);
		if(Spec->Ability->AbilityTags==AttackAbilityTagContainer)
		{
			if(Spec->IsActive())
			{
				FGameplayEffectContextHandle ContextHandle=EventData.ContextHandle;
				ContextHandle.AddHitResult(HitResult);
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(),FGameplayTag::RequestGameplayTag("Ability.Attack.Melee"),EventData);
				return;
			}
		}
	}
}