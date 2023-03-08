// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "GameFramework/Character.h"
#include "BaseMonster.generated.h"

DECLARE_DELEGATE_OneParam(FMonsterDieSignature, ABaseMonster*)

class UProgressBar;
class UWidgetComponent;
class USkeletalMeshComponent;
class UBaseMonsterAnimInstance;
struct FDamageEvent;
UCLASS()
class RETARGETINGTEST_API ABaseMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMonster();
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

private:
	UFUNCTION()
	void AttackCheck();

public:
	FMonsterDieSignature MonsterDieDelegate;

protected:
	UPROPERTY(VisibleAnywhere,Category=Stat)
	class UBaseMonsterStatComponent* StatComponent;
	
	//UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	//UWidgetComponent* HPWidgetComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	class UMonsterHPWidget* HPBarWidget;
	
private:

	UPROPERTY()
	UBaseMonsterAnimInstance* mAnimInstacne;
	
	float AttackRadius=200.0f;

	float AttackRange=350.0f;
	
};
