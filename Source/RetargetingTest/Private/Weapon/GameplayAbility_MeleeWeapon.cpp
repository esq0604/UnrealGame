// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GameplayAbility_MeleeWeapon.h"

#include "Engine/HitResult.h"
#include "Weapon/BaseWeaponInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"



UGameplayAbility_MeleeWeapon::UGameplayAbility_MeleeWeapon(const FObjectInitializer& ObjectInitializer)
{
}

ABaseWeaponInstance* UGameplayAbility_MeleeWeapon::GetWeaponInstance()
{
	if(FGameplayAbilitySpec* Spec = UGameplayAbility::GetCurrentAbilitySpec())
	{
		return Cast<ABaseWeaponInstance>(Spec->SourceObject.Get());
	}
	return nullptr;
}

void UGameplayAbility_MeleeWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CommitAbility(Handle,ActorInfo,ActivationInfo);

	
}

void UGameplayAbility_MeleeWeapon::PerformTrace(OUT TArray<FHitResult>& OutHits)
{
	APawn* const AvatarPawn = Cast<APawn>(GetAvatarActorFromActorInfo());
	ABaseWeaponInstance* WeaponInstance = GetWeaponInstance();

// #if ENABLE_DRAW_DEBUG
// 	
// 	//static float DebugThickness = 2.0f;
// 	//DrawDebugLine(GetWorld(), InputData.StartTrace, InputData.StartTrace + (InputData.AimDir * 100.0f), FColor::Yellow, false, LyraConsoleVariables::DrawBulletTracesDuration, 0, DebugThickness);
// 	FTransform StartTraceTransform =WeaponInstance->GetWeaponStateMeshComponent()->GetSocketTransform(WeaponInstance->GetWeaponTraceStartSocketName());
// 	FTransform EndTraceTransform = WeaponInstance->GetWeaponStateMeshComponent()->GetSocketTransform(WeaponInstance->GetWeaponTraceEndSocketName()); 
//
// #endif

}
