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
struct FDamageEvent;
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
	
	/* Getter */
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	UFUNCTION(BlueprintCallable)
	class UBasePlayerStatComponent* GetStatComponent() const;
	class UBaseStateManagerComponent* GetStateManagerComponent() const;
	UTexture2D* GetThumnailAtInventorySlot(int32 Slot) const;
	FString GetItemNameAtInventorySlot(int32 Slot) const;
	void UseItemAtInventorySlot(int32 Slot);
protected:

	//Input Action Bind Action 
	void Sprint(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintCallable)
	void JumpAndDodge();

	virtual void PostInitializeComponents() override;
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;


	void SprintEnd();
private:
	void ToggleInventory();

	void Interact();

	void CheckForInteractalbe();
public:
	//플레이어의 도움말입니다.
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="HUD")
	FString HelpText;

	//플레이어가 소유한 골드양을 나타냅니다.
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="HUD")
	int32 Gold;
	 
	UFUNCTION(BlueprintPure,Category="Inventory function")
	bool AddItemToInventory(APickUp* Item);
	APickUp* GetItemAtInventory(int32 Index);
	TArray<APickUp*> GetInventory() const;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	TArray<APickUp*> Inventory;
protected:
	UPROPERTY(VisibleInstanceOnly,BlueprintReadWrite,Category="Animation")
	class UCharaterAnimInstance* mAnimInstance;

	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess=true))
	class UFloatingCombatTextComponent* FloatingTextComponent;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* mStatWidgetComponent;
	UPROPERTY(EditAnywhere)
	class UPlayerStatWidget* StatBarWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Component")
	UBaseStateManagerComponent* StateManagerComponent;

	UPROPERTY(VisibleInstanceOnly,BlueprintReadWrite,Category=Move,meta=(AllowPrivateAccess=true))
	bool IsMoving;
	UPROPERTY(VisibleInstanceOnly,BlueprintReadWrite,Category=Move,meta=(AllowPrivateAccess=true))
	bool IsDodge;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inventory Test",meta=(AllowPrivateAccess=true))
	bool bInventoryShow;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inventory Test",meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Inventory Test",meta=(AllowPrivateAccess=true))
	class UInventory* Invenwidget;
	
private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;


	/*Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* IteractionAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ToggleInventoryAction;

	//PlayerComponent
	UPROPERTY(VisibleInstanceOnly,Category="Component")
	class UBasePlayerStatComponent* StatComponent;

	/*Attack*/
	UPROPERTY(VisibleAnywhere,Category="Weapon")
	USkeletalMeshComponent* Weapon;
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

	//Interact
	const float CheckInteractableReach=100.0f;
	
	class AInteractable* CurrentInteractable;

};

