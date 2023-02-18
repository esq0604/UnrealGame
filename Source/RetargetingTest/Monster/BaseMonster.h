// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "GameFramework/Character.h"
#include "BaseMonster.generated.h"

class USkeletalMeshComponent;

UCLASS()
class RETARGETINGTEST_API ABaseMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UMaterial* mDamagedMaterial;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UMaterial* mDefaultMaterial;
private:
    UPROPERTY(VisibleAnywhere, Category="Monster | Stat", meta=(AllowPrivateAccess="true"))
	float mHp;

	UPROPERTY(VisibleAnywhere, Category="Monster | Stat")
	float mAttackDamage;

	UPROPERTY(VisibleAnywhere, Category="Monster | Stat")
	float mSpeed;
	
	const int BODY_MATERIAL_IDX=0;

};
