// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_WeaponCollisionToggle.h"

#include "Interface/Combat.h"
#include "Kismet/KismetSystemLibrary.h"

void UAnimNotifyState_WeaponCollisionToggle::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                         float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	//캐스팅을 통해 인터페이스를 상속받았는지 확인합니다.
	ICombat* CombatInterface = Cast<ICombat>(MeshComp->GetOwner());
	if(CombatInterface)
	{
		CombatInterface->ToggleWeaponCollision_Implementation(true);
	}
}

void UAnimNotifyState_WeaponCollisionToggle::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	//캐스팅을 통해 인터페이스를 상속받았는지 확인합니다.
	ICombat* CombatInterface = Cast<ICombat>(MeshComp->GetOwner());
	if(CombatInterface)
	{
		CombatInterface->ToggleWeaponCollision_Implementation(false);
	}
}
