// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Weapon/BaseWeaponInstance.h"

#include "Ability/CharacterGameplayAbility.h"
#include "Component/CollisionComponent.h"
#include "RetargetingTest/Public/Controller/MyPlayerController.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"

// Sets default values
ABaseWeaponInstance::ABaseWeaponInstance()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	WeaponStaticMeshCompnent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	CollisionComp=CreateDefaultSubobject<UCollisionComponent>(TEXT("CollisionComp"));
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

void ABaseWeaponInstance::OnEquipped()
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	
	//AttachToActor(character,FAttachmentTransformRules::SnapToTargetIncludingScale,AttachSocketName);
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
	CollisionComp->SetCollisionMeshComp(WeaponStaticMeshCompnent);

	CollisionComp->OnHitDelegate.BindUObject(this,&ABaseWeaponInstance::OnHitDelegateFunction);
}

void ABaseWeaponInstance::OnHitDelegateFunction(FHitResult HitResult)
{
	UE_LOG(LogTemp,Warning,TEXT("OnHit DelegateFunction do Something"));
	//TODO : Attack Ability를 가져와서. HitResult를 넘겨줘야합니다, 별도의 캐스팅없이 실행하도록 해야합니다.
	Cast<ACharacterBase>(GetOwner())->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("Weapon.State.EnableCollision"));

}
