// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "Interface/Combat.h"
#include "Weapon/EHitReaction.h"
#include "CharacterBase.generated.h"


class ABaseWeaponInstance;
class UCharacterGameplayAbility;
class UCharacterAbilitySystemComponent;
class UBaseAttributeSet;
class UCharacterAttributeSetBase;
class UTargetingComponent;
class APlayerStateBase;
class UBaseAbilityManagerComponent;
class UWidgetComponent;
class UFloatingCombatTextComponent;
class UCharaterAnimInstance;
class UBasePlayerStatComponent;
class UInputMappingContext;
class UInputAction;
struct FDamageEvent;
class UMotionWarpingComponent;
class UStaticMeshComponent;
class UAbilitySystemComponent;
class USpringArmComponent;
class UCameraComponent;
class AItemBase;
class UInventoryComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterDied,ACharacterBase*,character);
UCLASS(config=Game)
class ACharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombat//, public IAttackable
{
	GENERATED_BODY()

public:
	ACharacterBase();

	UFUNCTION(BlueprintCallable)
	virtual void PossessedBy(AController* NewController) override;
	virtual int32 GetAbilityLevel() const;
	virtual void RemoveCharacterAbilities();
	virtual void OnRep_PlayerState() override;
	virtual void InitializeAttributes();
	virtual void GiveDefaultAbilities();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UBaseAttributeSet* GetAttributes() const;
	UInventoryComponent* GetInventoryManagerCompnent() const;

	void Die();
	
	
	UFUNCTION(BlueprintCallable)
	void AttackWithMotionWarp();
protected:
	virtual void PostInitializeComponents() override;

	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;

	virtual void ToggleWeaponCollision_Implementation(bool IsEnable) override;
	virtual UAnimMontage* GetHitReaction_Implementation(EHitDirection HitDirection) override;
public:
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="CharacterBase | Attributes")
	TArray<TSubclassOf<UGameplayEffect>> DefaultAttributeEffects;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="CharacterBase | Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"),Category="CharacterBase | Component")
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"),Category="CharacterBase | Component")
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(BlueprintAssignable,Category="CharacterBase| Died")
	FOnCharacterDied OnChracterDied;
	
	UFUNCTION(BlueprintCallable,Category="CharacterBase| Died")
	virtual void FinishDying();
protected:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	TObjectPtr<UFloatingCombatTextComponent> FloatingTextComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Component")
	TWeakObjectPtr<UCharacterAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Attributes")
	UBaseAttributeSet* Attributes;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | AnimInstance")
	TObjectPtr<UCharaterAnimInstance> AnimInstance;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Attack")
	TWeakObjectPtr<AActor> mHitActor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Weapon")
	TSubclassOf<ABaseWeaponInstance> WeaponClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Weapon")
	ABaseWeaponInstance* WeaponInstance;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Montage |HitReaction")
	TObjectPtr<UAnimMontage> ForwardHitReaction;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Montage |HitReaction")
	TObjectPtr<UAnimMontage> BackWardHitReaction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Montage |HitReaction")
	TObjectPtr<UAnimMontage> LeftHitReaction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Montage |HitReaction")
	TObjectPtr<UAnimMontage> RightHitReaction;

	
	// void BindASCInput();
	// bool ASCInputBound=false;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess="true"), Category="CharacterBase | Component")
	TObjectPtr<UMotionWarpingComponent> MotionWarpComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess="true"), Category="CharacterBase | Component")
	TObjectPtr<UInventoryComponent> InventoryManagerComponent;
};

