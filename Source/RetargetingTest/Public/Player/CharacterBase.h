// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "Interface/Attackable.h"
#include "Weapon/EHitReaction.h"
#include "CharacterBase.generated.h"


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
class URuneAttributeSet;
class UInventoryComponent;

UCLASS(config=Game)
class ACharacterBase : public ACharacter, public IAbilitySystemInterface, public IAttackable
{
	GENERATED_BODY()

public:
	ACharacterBase();

	UFUNCTION(BlueprintCallable)
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void InitializeAttributes();
	virtual void GiveDefaultAbilities();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	URuneAttributeSet* GetAttributes() const;

	UInventoryComponent* GetInventoryManagerCompnent() const;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void ToggleWeaponCollision(bool bIsEnable);
	virtual void ToggleWeaponCollision_Implementation(bool bIsEnable) override;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	AActor* GetHitActor();
	virtual AActor* GetHitActor_Implementation() override;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void SetHitActor(AActor* HitActor);
	virtual void SetHitActor_Implementation(AActor* HitActor) override;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	EHitReaction GetHitReaction();
	virtual EHitReaction GetHitReaction_Implementation() override;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void SetHitReaction(EHitReaction HitReaction);
	virtual void SetHitReaction_Implementation(EHitReaction HitReaction) override;
protected:
	virtual void PostInitializeComponents() override;

	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void WeaponCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
												 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
												 const FHitResult& SweepResult);

public:
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="CharacterBase | Attributes")
	TArray<TSubclassOf<UGameplayEffect>> DefaultAttributeEffects;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="CharacterBase | Attributes")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"),Category="CharacterBase | Component")
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"),Category="CharacterBase | Component")
	TObjectPtr<UCameraComponent> FollowCamera;


protected:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	TObjectPtr<UFloatingCombatTextComponent> FloatingTextComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Component")
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="CharacterBase | Component")
	TObjectPtr<UTargetingComponent> TargetingComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Attributes")
	URuneAttributeSet* Attributes;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | AnimInstance")
	TObjectPtr<UCharaterAnimInstance> AnimInstance;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=ture),Category="CharacterBase | Weapon")
	TObjectPtr<UStaticMeshComponent> Weapon;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Weapon")
	TObjectPtr<UCapsuleComponent> WeaponCollision;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | LookOnTarget")
	bool TargetLock{false};

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | LookOnTarget")
	TObjectPtr<AActor> TargetObject;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Attack")
	EHitReaction mHitReaction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="CharacterBase | Attack")
	TWeakObjectPtr<AActor> mHitActor;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess="true"), Category="CharacterBase | Component")
	TObjectPtr<UMotionWarpingComponent> MotionWarpComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess="true"), Category="CharacterBase | Component")
	TObjectPtr<UInventoryComponent> InventoryManagerComponent;

	
};

