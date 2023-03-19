// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/ItemBase.h"

#include "Kismet/GameplayStatics.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"
#include "RetargetingTest/UI/Public/Slot.h"
#include "Engine/Texture2D.h"


AItemBase::AItemBase()
{
	//픽업을 위한 메시를 설정하고 아이템 이름, 도움말 및 아이템 값을 설정합니다.
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	InteractableMesh->SetSimulatePhysics(true);
	ItemName = FString("Enter an item name here...");
	//InteractableHelpText=FString("Press E to pick item up.");
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void AItemBase::Interact_Implementation()
{
	ARetargetingTestCharacter* Character=Cast<ARetargetingTestCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));

	Character->AddItemToInventory(this);
	OnPickup();
}

/**
 * 아이템을 들고, 레벨에서 지워야할때 호출됩니다.
 * 아이템을 Distroy해버리면 , 캐릭터의 인벤토리에 아이템이 존재하지 않기때문에 지우지 않습니다.
 */
void AItemBase::OnPickup()
{
	InteractableMesh->SetVisibility(false);
	InteractableMesh->SetSimulatePhysics(false);
	InteractableMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AItemBase::AddReferenceSlot(USlot*& Slot)
{
	ReferenceSlot.AddUnique(Slot);
}

void AItemBase::RemoveReferenceSlot(USlot*& Slot)
{
	ReferenceSlot.RemoveSingle(Slot);
}

void AItemBase::UseItem(ARetargetingTestCharacter* Character)
{
	UE_LOG(LogTemp,Warning,TEXT("UseItem In AItemBase"));
}

