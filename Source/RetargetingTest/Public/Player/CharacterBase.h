// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "Interface/Combat.h"
#include "Interface/Interactable.h"
#include "CharacterBase.generated.h"


class ACustomHUD;
class UCustomSpringArmComponent;
class UTargetingComponent;
class UCustomGameplayAbility;
class ABaseWeaponItem;
class UBaseAttributeSet;
class UFloatingCombatTextComponent;
class UCharaterAnimInstance;
class UMotionWarpingComponent;
class UAbilitySystemComponent;
class UCameraComponent;
class UInventoryComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterDied,ACharacterBase*,character);


USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()
	
	FInteractionData() : CurrentInteractable(nullptr), LastInteractCheckTime(0.0f)
	{
	};
	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	float LastInteractCheckTime;
};


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
	virtual void OnRep_PlayerState() override final;
	virtual void InitializeAttributes();
	virtual void GiveDefaultAbilities();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override final;
	UBaseAttributeSet* GetAttributes() const;
	UInventoryComponent* GetInventoryManagerComponent() const;

	void SetWeaponInstance(ABaseWeaponItem* NewWeaponInstance);
	UFUNCTION(BlueprintCallable)
	E4WAYParryDirection GetParryHitDirection() const;
	void Die();

protected:
	virtual void PostInitializeComponents() override;

	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;

	virtual void ToggleWeaponCollision_Implementation(bool IsEnable) override final;
	virtual UAnimMontage* GetHitReaction_Implementation(EHitDirection HitDirection) override final;
	virtual UAnimMontage* GetParryMontage_Implementation(EHitDirection HitDirection) override;
	virtual bool CanReceivedDamaged_Implementation() override;
	virtual void SetIFrame_Implementation(bool bEnabled) override;

	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();
	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction);}
	
public:
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="CharacterBase | Attributes")
	TArray<TSubclassOf<UGameplayEffect>> DefaultAttributeEffects;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="CharacterBase | Ability")
	TArray<TSubclassOf<UCustomGameplayAbility>> DefaultAbilities;
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"),Category="CharacterBase | Component")
	UCustomSpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"),Category="CharacterBase | Component")
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(BlueprintAssignable,Category="CharacterBase| Died")
	FOnCharacterDied OnChracterDied;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lock On Camera")
	float LockonControlRotationRate=10.f;
	
	UFUNCTION(BlueprintCallable,Category="CharacterBase| Died")
	virtual void FinishDying();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	TObjectPtr<UFloatingCombatTextComponent> FloatingTextComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Component")
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Attributes")
	UBaseAttributeSet* Attributes;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | AnimInstance")
	TObjectPtr<UCharaterAnimInstance> AnimInstance;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Attack")
	TWeakObjectPtr<AActor> mHitActor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Weapon")
	TSubclassOf<ABaseWeaponItem> WeaponClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Weapon")
	ABaseWeaponItem* WeaponInstance;

	//Hit Reaction
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Montage |HitReaction")
	TObjectPtr<UAnimMontage> ForwardHitReaction;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Montage |HitReaction")
	TObjectPtr<UAnimMontage> BackWardHitReaction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Montage |HitReaction")
	TObjectPtr<UAnimMontage> LeftHitReaction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Montage |HitReaction")
	TObjectPtr<UAnimMontage> RightHitReaction;


	//Parry
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Montage | Parry")
	TObjectPtr<UAnimMontage> ParryLeft;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Montage | Parry")
	TObjectPtr<UAnimMontage> ParryRight;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Montage | Parry")
	TObjectPtr<UAnimMontage> ParryUp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Montage | Parry")
	TObjectPtr<UAnimMontage> ParryDown;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Montage | Parry")
	E4WAYParryDirection ParryHitDirection;

	UPROPERTY(VisibleAnywhere,Category="CharacterBase | Interaction")
	TScriptInterface<IInteractable> TargetInteractable;

	float InteractionCheckFrequency{0.1f};
	float InteractionCheckDistance{225.0f};
	FTimerHandle TimerHandle_Interaction;
	FInteractionData InteractionData;

	UPROPERTY()
	TObjectPtr<ACustomHUD> HUD;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess=true), Category="CharacterBase | Component")
	TObjectPtr<UMotionWarpingComponent> MotionWarpComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess=true), Category="CharacterBase | Component")
	TObjectPtr<UInventoryComponent> InventoryManagerComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	bool bIFrame;
};
