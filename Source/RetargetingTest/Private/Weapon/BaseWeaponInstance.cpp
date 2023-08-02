// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Weapon/BaseWeaponInstance.h"

#include "Ability/CharacterGameplayAbility.h"
#include "RetargetingTest/Public/Controller/MyPlayerController.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"

// Sets default values
ABaseWeaponInstance::ABaseWeaponInstance()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	WeaponMeshCompnent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
}

UAbilitySystemComponent* ABaseWeaponInstance::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseWeaponInstance::AddAbilities()
{
	for (TSubclassOf<UGameplayAbility>& Ability : Abilities)
	{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(),1,0,this));
	}
}

void ABaseWeaponInstance::RemoveAbilities()
{
}

void ABaseWeaponInstance::SetOwningCharacter(ACharacterBase* InOwningCharacter)
{
	OwningCharacter = InOwningCharacter;
	AbilitySystemComponent = OwningCharacter->GetAbilitySystemComponent();
	SetOwner(InOwningCharacter);
}

// Called when the game starts or when spawned
void ABaseWeaponInstance::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeaponInstance::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}



