// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "CharacterBase.generated.h"


class ABaseWeapon;
class UBaseAbilityManagerComponent;
class UAttackComponent;
class UBaseStatComponent;
class APlayerAttackComponent;
class APlayerStatComponent;
class UWidgetComponent;
class UPlayerGauge;
class UFloatingCombatTextComponent;
class UCharaterAnimInstance;
class UBasePlayerStatComponent;
class UPlayerHUD;
class UInputMappingContext;
class UInputAction;
struct FDamageEvent;
class UMotionWarpingComponent;
class UStaticMeshComponent;
class UAbilitySystemComponent;

//TODO : CharacterBase 클래스이므로, 플레이어 클래스를 따로 나누어 CharacterBase에 존재하는 Player 속성들을 옮겨야합니다.
UCLASS(config=Game)
class ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintCallable, Category="Inventory function")
	void UseItemAtInventorySlot(int32 Slot);

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void InitializeAttributes();
	virtual void GiveDefaultAbilities();
	
	/* Setter */
	UFUNCTION(BlueprintCallable, Category="Setter")
	void SetbCanbeDamaged(bool canBeDamage) { bCanDamaged = canBeDamage; }

	UFUNCTION(BlueprintCallable, Category="Setter")
	bool AddItemToInventory(AItemBase* Item);

	/* Getter */
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	UFUNCTION(BlueprintCallable, Category="Getter")
	TArray<AItemBase*> GetInventory() const;

	UFUNCTION(BlueprintCallable, Category="Getter")
	AItemBase* GetItemAtInventory(int32 Index);

	UFUNCTION(BlueprintCallable, Category="Getter")
	UTexture2D* GetThumnailAtInventorySlot(int32 Slot) const;

	UFUNCTION(BlueprintCallable, Category="Getter")
	FString GetItemNameAtInventorySlot(int32 Slot) const;

	UFUNCTION(BlueprintCallable, Category="Getter")
	UBasePlayerStatComponent* GetStatComponent() const;

	UFUNCTION(BlueprintCallable, Category="Getter")
	UBaseAbilityManagerComponent* GetAbilityManagerComponent() const;

	UFUNCTION(BlueprintCallable, Category="Getter")
	ABaseWeapon* GetEquipedWeapon() const;

protected:
	//Input Action Bind Action 
	void Sprint(const FInputActionValue& Value);


	UFUNCTION(BlueprintCallable)
	void JumpAndDodge();

	virtual void PostInitializeComponents() override;

	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;

	//UFUNCTION(BlueprintCallable,Category="Attack Function")
	//void Attack(const FInputActionValue& Value);
	//UFUNCTION(BlueprintCallable,Category="Attack Function")
	//void AttackCheck();
	//UFUNCTION(BlueprintCallable,Category="Attack Function")
	//void AttackStartComboState();
	//UFUNCTION(BlueprintCallable,Category="Attack Function")
	//void AttackEndComboState();

private:
	void SprintEnd();
	void ToggleInventory();
	void Interact();
	void CheckForInteractalbe();
	void UseQuickSlot(int UsedSlotIdx);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TArray<AItemBase*> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	float MaxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	float MaxMana = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	float MaxStamina = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	float MaxStat = 99;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;
	
protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Animation")
	UCharaterAnimInstance* mAnimInstance;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	UFloatingCombatTextComponent* FloatingTextComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
	UMotionWarpingComponent* MotionWarpComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
	UBaseAbilityManagerComponent* AbilityManagerComponent;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category=Dodge, meta=(AllowPrivateAccess=true))
	bool IsDodge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HUD", meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> PlayerHUDClass;

	UPROPERTY(VisibleAnywhere, Category="HUD", meta=(AllowPrivateAccess=true))
	UPlayerHUD* PlayerHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true), Category="Weapon")
	TSubclassOf<ABaseWeapon> EquipedWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true), Category="Weapon")
	ABaseWeapon* EquipedWeapon;

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	//PlayerComponent
	UPROPERTY(VisibleInstanceOnly, Category="Component")
	UBasePlayerStatComponent* StatComponent;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Attack", meta=(AllowPrivateAccess=true))
	float AttackRange;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Attack", meta=(AllowPrivateAccess=true))
	float AttackRadius;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category= Attack, meta=(AllowPrivateAccess=true))
	bool CanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Attack, meta=(AllowPrivateAccess=true))
	bool IsComboInputOn;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Attack, meta=(AllowPrivateAccess=true))
	int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Attack, meta=(AllowPrivateAccess=true))
	int32 MaxCombo;
	const int32 MAX_COMBO = 4;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Attack, meta=(AllowPrivateAccess=true))
	bool IsAttacking;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UAnimMontage* DodgeMontage;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess=true))
	bool bCanDamaged = true;
	//Interact
	const float CheckInteractableReach = 100.0f;

	AItemBase* CurrentInteractable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Abilities", meta=(AllowPrivateAccess="true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class URuneAttributeSet* Attributes;


};
