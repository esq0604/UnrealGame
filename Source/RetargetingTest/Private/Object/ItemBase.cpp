// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Object/ItemBase.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Texture2D.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"


AItemBase::AItemBase()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SetRootComponent(StaticMeshComponent);
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

/**
 * 아이템을 들고, 레벨에서 지워야할때 호출됩니다.
 * 아이템을 Distroy해버리면 , 캐릭터의 인벤토리에 아이템이 존재하지 않기때문에 지우지 않습니다.
 */
void AItemBase::OnPickup()
{

}

void AItemBase::AddReferenceSlot(USlot*& Slot)
{
	ReferenceSlot.AddUnique(Slot);
}

void AItemBase::RemoveReferenceSlot(USlot*& Slot)
{
	ReferenceSlot.RemoveSingle(Slot);
}

UTexture2D* AItemBase::GetThumbnail() const
{
	return nullptr;
}

void AItemBase::SetItemData(UItemDataAsset* Data)
{
}

