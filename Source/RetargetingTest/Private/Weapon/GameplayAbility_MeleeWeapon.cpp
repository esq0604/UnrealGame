// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GameplayAbility_MeleeWeapon.h"

#include "Engine/HitResult.h"
#include "Weapon/BaseWeaponInstance.h"
#include "Kismet/KismetSystemLibrary.h"


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

void UGameplayAbility_MeleeWeapon::StartWeaponTraceForTarget()
{
	check(CurrentActorInfo);
	AActor* AvartaActor = CurrentActorInfo->AvatarActor.Get();
	
	UAbilitySystemComponent* MyAbilityComponent = CurrentActorInfo->AbilitySystemComponent.Get();
	check(MyAbilityComponent);

	AController* Controller = CurrentActorInfo->PlayerController.Get();
	check(Controller);

	TArray<FHitResult> FoundHits;
	PerformTrace(FoundHits);
	
	
}
