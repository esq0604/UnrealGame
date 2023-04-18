// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Weapon/public/BaseWeapon.h"

#include "RetargetingTest/Ability/public/BaseAbilityObject.h"
#include "RetargetingTest/Component/Public/BaseAbilityManagerComponent.h"
#include "RetargetingTest/Player/Public/CharacterBase.h"
#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"
#include "RetargetingTest/Controller/public/MyPlayerController.h"
#include "RetargetingTest/Weapon/public/PDAWeapon.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	WeaponMeshCompnent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UPDAWeapon* ABaseWeapon::GetWeaponDataAsset() const
{
	return WeaponDataAsset;
}

void ABaseWeapon::CreateWeaponStateAndAbility()
{
	AMyPlayerController* LocalController = dynamic_cast<AMyPlayerController*>(GetWorld()->GetFirstPlayerController());
	{
		for(TSubclassOf<UBaseStateObject> StateToCreate: WeaponDataAsset->StatesToCreate)
		{
			LocalController->GetStateManagerComponent()->ConstructStateOfClass(StateToCreate);
			
		}
	}
	FGameplayTag IdleStateTag = FGameplayTag::RequestGameplayTag("State.Idle");
	LocalController->GetStateManagerComponent()->PerformStateOfClass(LocalController->GetStateManagerComponent()->GetStateOfGameplayTag(IdleStateTag)->GetClass());

	ACharacterBase* LocalCharacterBase = dynamic_cast<ACharacterBase*>(LocalController->GetCharacter());
	UBaseAbilityManagerComponent* LocalAbilityComponent = LocalCharacterBase->GetAbilityManagerComponent();
	for(FAbilityMontage AbilityMontage : WeaponDataAsset->Abilities)
	{
		LocalAbilityComponent->ConstructAbilityOfClass(AbilityMontage.Ability);
	}
	
}

void ABaseWeapon::EquipWeapon()
{
	const ACharacterBase* LocalCharacter = dynamic_cast<ACharacterBase*>(GetOwner());
	CreateWeaponStateAndAbility();
	if(LocalCharacter!= nullptr)
	{
		WeaponMeshCompnent->SetStaticMesh(WeaponMesh);
		AttachToComponent(LocalCharacter->GetMesh(),FAttachmentTransformRules(EAttachmentRule::SnapToTarget,true),FName("Weapon_Back"));
	}

}


