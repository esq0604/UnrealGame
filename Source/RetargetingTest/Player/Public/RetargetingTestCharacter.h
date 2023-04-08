// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "RetargetingTestCharacter.generated.h"


class UBaseStateManagerComponent;
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

UCLASS(config=Game)
class ARetargetingTestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARetargetingTestCharacter();

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void AttackCheck();
	void AttackStartComboState();
	void AttackEndComboState();

	UFUNCTION()
	void OnAttackMontageEnded(class UAnimMontage* Montage, bool bInterrupted);


	/* Setter */
	void SetbCanbeDamaged(bool canBeDamage) {bCanDamaged=canBeDamage;}
	/* Getter */
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	UFUNCTION(BlueprintCallable)
	UBasePlayerStatComponent* GetStatComponent() const;
	
	UBaseStateManagerComponent* GetStateManagerComponent() const;
	UTexture2D* GetThumnailAtInventorySlot(int32 Slot) const;
	FString GetItemNameAtInventorySlot(int32 Slot) const;
	void UseItemAtInventorySlot(int32 Slot);

	UFUNCTION(BlueprintPure,Category="Inventory function")
	bool AddItemToInventory(AItemBase* Item);
	AItemBase* GetItemAtInventory(int32 Index);
	TArray<AItemBase*> GetInventory() const;

protected:

	//Input Action Bind Action 
	void Sprint(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintCallable)
	void JumpAndDodge();

	virtual void PostInitializeComponents() override;

	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;
	
	
private:
	void SprintEnd();
	void ToggleInventory();
	void Interact();
	void CheckForInteractalbe();
	void UseQuickSlot(int UsedSlotIdx);
public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	TArray<AItemBase*> Inventory;
protected:
	UPROPERTY(VisibleInstanceOnly,BlueprintReadWrite,Category="Animation")
	UCharaterAnimInstance* mAnimInstance;

	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess=true))
	UFloatingCombatTextComponent* FloatingTextComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Component")
	UBaseStateManagerComponent* StateManagerComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Component")
	UMotionWarpingComponent* MotionWarpComponent;
	
	UPROPERTY(VisibleInstanceOnly,BlueprintReadWrite,Category=Dodge,meta=(AllowPrivateAccess=true))
	bool IsDodge;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="HUD",meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> PlayerHUDClass;

	UPROPERTY(VisibleAnywhere,Category="HUD",meta=(AllowPrivateAccess=true))
	UPlayerHUD* PlayerHUD;
private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	//PlayerComponent
	UPROPERTY(VisibleInstanceOnly,Category="Component")
	UBasePlayerStatComponent* StatComponent;
	
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly,Category="Attack",meta=(AllowPrivateAccess=true))
	float AttackRange;
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly,Category="Attack",meta=(AllowPrivateAccess=true))
	float AttackRadius;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category= Attack, meta=(AllowPrivateAccess=true))
	bool CanNextCombo;
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly,Category=Attack,meta=(AllowPrivateAccess=true))
	bool IsComboInputOn;
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly,Category=Attack,meta=(AllowPrivateAccess=true))
	int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly,Category=Attack,meta=(AllowPrivateAccess=true))
	int32 MaxCombo;
	const int32 MAX_COMBO =4;
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly,Category=Attack,meta=(AllowPrivateAccess=true))
	bool IsAttacking;
	
	UPROPERTY(BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UAnimMontage* DodgeMontage;

	UPROPERTY(VisibleAnywhere,meta=(AllowPrivateAccess=true))
	bool bCanDamaged=true;
	//Interact
	const float CheckInteractableReach=100.0f;
	
	AItemBase* CurrentInteractable;

};

