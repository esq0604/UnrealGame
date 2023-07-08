// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseMonster.generated.h"

class UBaseAttributeSet;
class UBehaviorTree;
class UWidgetComponent;
class UEnemyAttributeSetBase;
DECLARE_DELEGATE_OneParam(FMonsterDieSignature, ABaseMonster*)

class UProgressBar;
class USkeletalMeshComponent;
class UBaseMonsterAnimInstance;
class UGameplayEffect;
class UGameplayAbility;
class UMonsterGauge;

struct FOnAttributeChangeData;
struct FDamageEvent;
UCLASS()
class RETARGETINGTEST_API ABaseMonster : public ACharacter,public IAbilitySystemInterface//, public IAttackable,public ITargeting
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMonster();
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void InitializeAttributes();
	virtual void GiveDefaultAbilities();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void SpawnInit();
	// UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	// void ToggleWeaponCollision(bool bIsEnable);
	// virtual void ToggleWeaponCollision_Implementation(bool bIsEnable) override;
	//
	// UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	// AActor* GetHitActor();
	// virtual AActor* GetHitActor_Implementation() override;
	//
	// UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	// void SetHitActor(AActor* HitActor);
	// virtual void SetHitActor_Implementation(AActor* HitActor) override;
	//
	// UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	// EHitReaction GetHitReaction();
	// virtual EHitReaction GetHitReaction_Implementation() override;
	//
	// UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	// void SetHitReaction(EHitReaction HitReaction);
	// virtual void SetHitReaction_Implementation(EHitReaction HitReaction) override;

	UFUNCTION()
	void AttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
												 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
												 const FHitResult& SweepResult);
	
	TObjectPtr<UBehaviorTree> GetBehaviorTree() const;

	// UFUNCTION(BlueprintCallable)
	// void OnTargetSet(TWeakObjectPtr<AActor> NewTarget);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
private:
	virtual void HealthChange(const FOnAttributeChangeData& Data);


public:
	FMonsterDieSignature MonsterDieDelegate;

protected:
	/**
	 * 어빌리티 및 어트리뷰트
	 */
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="EnemyBase | Attributes")
	TArray<TSubclassOf<UGameplayEffect>> DefaultAttributeEffects;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="EnemyBase | Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Attributes")
	UBaseAttributeSet* Attributes;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Component")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	/**
	 * 에너미 위젯
	 */
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Component")
	TObjectPtr<UWidgetComponent> HPWidgetComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | HPWidget")
	TWeakObjectPtr<UMonsterGauge> HPBarWidget;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | UI")
	TSubclassOf<UUserWidget> HpWidgetClass;
	/**
	 * 초기화
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Initialize | Anim")
	TObjectPtr<UBaseMonsterAnimInstance> mAnimInstacne;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Initialize |Anim")
	TObjectPtr<UAnimMontage> DeadAnim;

	/*
	 * 몬스터 적 액터정보
	 */
	TObjectPtr<AActor> mHitActor;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	TObjectPtr<AActor> TargetActor;


	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Initialize | AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	FDelegateHandle HealthChangeDelegateHandle;
	FDelegateHandle MaxHealthChangeDelegateHandle;
};
