// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Weapon/BaseWeaponInstance.h"

#include "Ability/CharacterGameplayAbility.h"
#include "Component/CollisionComponent.h"
#include "RetargetingTest/Public/Controller/MyPlayerController.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"
#include "Weapon/GameplayAbility_MeleeWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemGlobals.h"

// Sets default values
ABaseWeaponInstance::ABaseWeaponInstance()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	WeaponStaticMeshCompnent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	//CollisionComp=CreateDefaultSubobject<UCollisionComponent>(TEXT("CollisionComp"));
	AbilitySystemComponent=CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
}

UAbilitySystemComponent* ABaseWeaponInstance::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseWeaponInstance::AddAbilities()
{
	for (TSubclassOf<UGameplayAbility>& Ability : Abilities)
	{
		AbilitySpecHandles.Add(AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(),1,0,this)));
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
	AbilitySystemComponent=UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
}

void ABaseWeaponInstance::OnEquipped()
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	
	AttachToComponent(character->GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,AttachSocketName);
}

FName ABaseWeaponInstance::GetWeaponTraceStartSocketName()
{
	return WeaponTraceStartSocketName;
}

FName ABaseWeaponInstance::GetWeaponTraceEndSocketName()
{
	return WeaponTraceEndSocketName;
}

// Called when the game starts or when spawned
void ABaseWeaponInstance::BeginPlay()
{
	Super::BeginPlay();
	WeaponStaticMeshCompnent->SetStaticMesh(WeaponStaticMesh);		
}

void ABaseWeaponInstance::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//CollisionComp->SetCollisionMeshComp(WeaponStaticMeshCompnent);
	//CollisionComp->OnHitDelegate.BindUObject(this,&ABaseWeaponInstance::OnHitDelegateFunction);
}

// void ABaseWeaponInstance::OnHitDelegateFunction(FHitResult HitResult)
// {
// 	TArray<FGameplayAbilitySpec*> StoreSpec;
// 	for(FGameplayAbilitySpecHandle SpecHandle : AbilitySpecHandles)
// 	{
// 		AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(AttackAbilityTagContainer,StoreSpec);
// 		for(FGameplayAbilitySpec* Spec : StoreSpec)
// 		{
// 			if(Spec->IsActive())
// 			{
// 				Cast<UGameplayAbility_MeleeWeapon>(Spec->Ability)->SetHitResult(HitResult);
// 			}
// 		}
// 	}
// 	UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner())->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("Weapon.State.EnableCollision"));
// }
