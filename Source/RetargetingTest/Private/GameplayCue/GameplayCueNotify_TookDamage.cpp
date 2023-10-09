// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayCue/GameplayCueNotify_TookDamage.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "Interface/Combat.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/FloatingDamageActor.h"

UGameplayCueNotify_TookDamage::UGameplayCueNotify_TookDamage()
{
	//GameplayCueTag=FGameplayTag::RequestGameplayTag("GameplayCue.TookDamage");
}

bool UGameplayCueNotify_TookDamage::OnExecute_Implementation(AActor* MyTarget,
                                                             const FGameplayCueParameters& Parameters) const
{
	const FGameplayEffectContextHandle ContextHandle = Parameters.EffectContext;
	const FHitResult* HitResult = ContextHandle.GetHitResult();
	
	if(MyTarget)
	{
		ACharacter* TargetCharacter = Cast<ACharacter>(MyTarget);
		UAnimMontage* SelectedMontage = SelectHitReaction(HitResult->Normal,HitResult->GetActor());
		TargetCharacter->PlayAnimMontage(SelectedMontage);
	}
	

	//SpawnFloatingDamage(ContextHandle.GetInstigator(),MyTarget);
	return Super::OnExecute_Implementation(MyTarget, Parameters);
}

bool UGameplayCueNotify_TookDamage::OnActive_Implementation(AActor* MyTarget,
	const FGameplayCueParameters& Parameters) const
{
	return Super::OnActive_Implementation(MyTarget, Parameters);

}

/**
 * HitReaction 반환 몽타주에 대한 구현여부를 확인하고, 방향을 계산해서 방향에 맞는 몽타주를 반환합니다.
 * @param HitNormal : HitActor와 EffectContext를 전달해준 액터와의 Normal벡터입니다.
 * @param HitActor : 공격을 맞은 대상 액터입니다.
 */
UAnimMontage* UGameplayCueNotify_TookDamage::SelectHitReaction(FVector HitNormal, AActor* HitActor) const
{
	UAnimMontage* MontagePick=nullptr;

	const float DotProduct_Forward = FVector::DotProduct(HitActor->GetActorForwardVector(),HitNormal);

	const float DotProduct_Right = FVector::DotProduct(HitActor->GetActorRightVector(),HitNormal);
	
	if(UKismetSystemLibrary::DoesImplementInterface(HitActor,UCombat::StaticClass()))
	{
		if(UKismetMathLibrary::InRange_FloatFloat(DotProduct_Right,-0.5f,0.5f,true,true))
		{
		
			//Fwd
			if(DotProduct_Forward > 0)
			{
				MontagePick=Cast<ICombat>(HitActor)->Execute_GetHitReaction(HitActor,EHitDirection::Forward);
			}
			//Bwd
			else
			{
				MontagePick=Cast<ICombat>(HitActor)->Execute_GetHitReaction(HitActor,EHitDirection::Backward);
			}
		}
		else
		{
			//Right
			if(DotProduct_Right > 0)
			{
				MontagePick=Cast<ICombat>(HitActor)->Execute_GetHitReaction(HitActor,EHitDirection::Right);
			}
			//Left
			else
			{
				MontagePick=Cast<ICombat>(HitActor)->Execute_GetHitReaction(HitActor,EHitDirection::Left);
			}
		}
	}
	
	return MontagePick;
}

void UGameplayCueNotify_TookDamage::SpawnFloatingDamage(AActor* Instigator,AActor* Target) const
{
	TObjectPtr<AFloatingDamageActor> FloatingDamageActor = GetWorld()->SpawnActorDeferred<AFloatingDamageActor>(FloatingDamageActorClass,Target->GetTransform(),Instigator);
	if(!FloatingDamageActor)
		return;
	
	FloatingDamageActor->InitSpawnDeferred();
	TObjectPtr<AActor> FloatingDamageActorSpawned = UGameplayStatics::FinishSpawningActor(FloatingDamageActor,Target->GetTransform());
}
