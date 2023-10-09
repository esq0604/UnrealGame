// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/Combat.h"
#include "Interface/Targeting.h"
#include "BaseMonster.generated.h"

class UMotionWarpingComponent;
class ABaseWeaponInstance;
class UWeaponCollisionComponent;
class UBaseAttributeSet;
class UBehaviorTree;
class UWidgetComponent;
class UEnemyAttributeSetBase;
DECLARE_DELEGATE_OneParam(FMonsterDieSignature, AActor*)

class UProgressBar;
class USkeletalMeshComponent;
class UBaseMonsterAnimInstance;
class UGameplayEffect;
class UGameplayAbility;
class UMonsterGauge;

struct FOnAttributeChangeData;
struct FDamageEvent;

UCLASS()
class RETARGETINGTEST_API ABaseMonster : public ACharacter,public IAbilitySystemInterface,public ICombat, public ITargeting
{
	GENERATED_BODY() //Generated.h생성 매크로

public:
	// Sets default values for this character's properties
	ABaseMonster();
	
	virtual void InitializeAttributes();
	virtual void GiveDefaultAbilities();

	//	IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void SpawnInit();
	UBehaviorTree* GetBehaviorTree() const;

	
	// ICombat
	virtual void ToggleWeaponCollision_Implementation(bool IsEnable) override final;
	virtual UAnimMontage* GetHitReaction_Implementation(EHitDirection HitDirection) override final;
	virtual UAnimMontage* GetParryMontage_Implementation(EHitDirection HitDirection) override;
	virtual bool CanReceivedDamaged_Implementation() override;
	virtual void SetIFrame_Implementation(bool bEnabled) override;
	UFUNCTION(BlueprintImplementableEvent)
	void DoDead();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;


	// ITargeting
	virtual void OnTargeted_Implementation(bool bIsTargeted) override;
	virtual bool CanBeTargeted_Implementation() override;

	//MotionWarp
	UFUNCTION(BlueprintCallable)
	void MotionWarpForwardToDistance(float MoveDistance);

private:
	virtual void HealthChange(const FOnAttributeChangeData& Data);
	virtual void ShowHpWidget(bool bShow) PURE_VIRTUAL(ABaseMonster::ShowHpWidget);

public:
	FMonsterDieSignature MonsterDieDelegate;
	 

protected:
	/**
	 * 컴포넌트
	 */

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="Enemy|Component")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;
	/**
	 * 어빌리티 및 어트리뷰트
	 */
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="EnemyBase | Attributes")
	TArray<TSubclassOf<UGameplayEffect>> DefaultAttributeEffects;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="EnemyBase | Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="EnemyBase | Attributes")
	UBaseAttributeSet* EnemyAttributesSet;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Component")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	

	/**
	 * 에너미 위젯
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="EnemyBase | Componnet")
	TObjectPtr<UWidgetComponent> TargetWidgetComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | UI")
	TSubclassOf<UUserWidget> TargetWidgetClass;
	

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | UI")
	TObjectPtr<UMonsterGauge> HPBarWidget;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | UI")
	TSubclassOf<UUserWidget> HpWidgetClass;
	
	/**
	 * 초기화
	 */
	// Anim
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Initialize | Anim")
	TObjectPtr<UBaseMonsterAnimInstance> mAnimInstacne;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Initialize |Anim")
	TObjectPtr<UAnimMontage> DeadAnim;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Initialize |Anim")
	TObjectPtr<UAnimMontage> ForwardHitReaction;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Initialize |Anim")
	TObjectPtr<UAnimMontage> BackWardHitReaction;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Initialize |Anim")
	TObjectPtr<UAnimMontage> LeftHitReaction;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Initialize |Anim")
	TObjectPtr<UAnimMontage> RightHitReaction;
	
	// Weapon
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="EnemyBase | Initialize | Weapon")
	TObjectPtr<ABaseWeaponInstance> WeaponInstance;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Initialize | Weapon")
	TSubclassOf<ABaseWeaponInstance> WeaponClass;
	
	// AI
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Initialize | AI")
	UBehaviorTree* BehaviorTreeAsset;

	/*
	 * 몬스터 적 액터정보
	 */
	TObjectPtr<AActor> HitActor;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true), Category="EnemyBase | Combat")
	TObjectPtr<AActor> TargetActor;


	
	FDelegateHandle HealthChangeDelegateHandle;
	FDelegateHandle MaxHealthChangeDelegateHandle;

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	bool bIFrame;
	
};
