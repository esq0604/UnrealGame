// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Ability/Public/BasePlayerAbility.h"

#include "RetargetingTest/Component/Public/BaseAbilityManagerComponent.h"
#include "RetargetingTest/Player/Public/CharacterBase.h"
#include "RetargetingTest/Weapon/public/BaseWeapon.h"
#include "RetargetingTest/Weapon/public/PDAWeapon.h"

UBasePlayerAbility::UBasePlayerAbility()
{
}

void UBasePlayerAbility::EndAbility()
{
	Super::EndAbility();
	UE_LOG(LogTemp,Warning,TEXT("PlayerAbility EndAbility"));
	AbilityManagerComponent->SetCurrentActiveAbility(nullptr);
}

TArray<UAnimMontage*> UBasePlayerAbility::GetAbilityMontage(TSubclassOf<UBaseAbilityObject> AbilityToLookFor)
{
	ACharacterBase* LocalCharacater=dynamic_cast<ACharacterBase*>(PerformingActor);

	TArray<FAbilityMontage> LocalAbilityMontages=LocalCharacater->GetEquipedWeapon()->GetWeaponDataAsset()->Abilities;

	for(FAbilityMontage LocalAbilityMontage : LocalAbilityMontages)
	{
		if(LocalAbilityMontage.Ability==AbilityToLookFor)
		{
			return LocalAbilityMontage.ListOfMontage;
		}
	}
	return TArray<UAnimMontage*>();
}
