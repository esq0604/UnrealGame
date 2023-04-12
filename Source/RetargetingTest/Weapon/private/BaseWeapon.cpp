// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Weapon/public/BaseWeapon.h"
#include "RetargetingTest/Player/Public/CharacterBase.h"
#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"
#include "RetargetingTest/Controller/public/MyPlayerController.h"
#include "RetargetingTest/Object/Public/BaseStateObject.h"
#include "RetargetingTest/Weapon/public/PDAWeapon.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	//ACharacterBase* LocalCharacter = dynamic_cast<ACharacterBase*>(GetOwner());


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

void ABaseWeapon::CreateWeaponStateAndAbility()
{
	AMyPlayerController* LocalController = dynamic_cast<AMyPlayerController*>(GetWorld()->GetFirstPlayerController());
	{
		for(int i=0; i<WeaponDataAsset->StatesToCreate.Num();i++)
		{
			LocalController->GetStateManagerComponent()->ConstructStateOfClass(WeaponDataAsset->StatesToCreate[i]);
			
		}
	}
}

