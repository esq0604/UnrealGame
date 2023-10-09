// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GameplayCueNotify_TookDamage.generated.h"

class AFloatingDamageActor;
struct FGameplayCueTag;
/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API UGameplayCueNotify_TookDamage : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
	
	UGameplayCueNotify_TookDamage();
protected:
	UFUNCTION()
	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;
	UFUNCTION()
	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;
	UAnimMontage* SelectHitReaction(FVector HitNormal, AActor* HitActor) const;

	UFUNCTION(BlueprintCallable)
	void SpawnFloatingDamage(AActor* Instigator,AActor* Target) const;
protected:
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,meta=(AllowPrivateAccess=true))
	TSubclassOf<AFloatingDamageActor> FloatingDamageActorClass;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,meta=(AllowPrivateAccess=true))
	TObjectPtr<USoundWave> HitSound;

};
