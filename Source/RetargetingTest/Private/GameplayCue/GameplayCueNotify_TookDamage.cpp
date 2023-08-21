// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayCue/GameplayCueNotify_TookDamage.h"

#include "GameFramework/Character.h"
#include "Interface/Combat.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UGameplayCueNotify_TookDamage::UGameplayCueNotify_TookDamage()
{
	GameplayCueTag=FGameplayTag::RequestGameplayTag("GameplayCue.TookDamage");
}

bool UGameplayCueNotify_TookDamage::OnExecute_Implementation(AActor* MyTarget,
                                                             const FGameplayCueParameters& Parameters) const
{
	UE_LOG(LogTemp,Warning,TEXT("HitReact "));
	const FGameplayEffectContextHandle ContextHandle = Parameters.EffectContext;
	const FHitResult* HitResult = ContextHandle.GetHitResult();
	
	if(MyTarget)
	{
		ACharacter* TargetCharacter = Cast<ACharacter>(MyTarget);
		UAnimMontage* SelectedMontage = SelectHitReaction(HitResult->Normal,HitResult->GetActor());
		TargetCharacter->PlayAnimMontage(SelectedMontage);
	}
	
	return Super::OnExecute_Implementation(MyTarget, Parameters);
}

bool UGameplayCueNotify_TookDamage::OnActive_Implementation(AActor* MyTarget,
	const FGameplayCueParameters& Parameters) const
{
	UE_LOG(LogTemp,Warning,TEXT("OnActive"));
	return Super::OnActive_Implementation(MyTarget, Parameters);

}

UAnimMontage* UGameplayCueNotify_TookDamage::SelectHitReaction(FVector HitNormal, AActor* HitActor) const
{
	UAnimMontage* MontagePick=nullptr;

	const float DotProduct_Forward = FVector::DotProduct(HitActor->GetActorForwardVector(),HitNormal);

	const float DotProduct_Right = FVector::DotProduct(HitActor->GetActorRightVector(),HitNormal);

	if(UKismetMathLibrary::InRange_FloatFloat(DotProduct_Right,-0.5f,0.5f,true,true))
	{
		if(UKismetSystemLibrary::DoesImplementInterface(HitActor,UCombat::StaticClass()))
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
