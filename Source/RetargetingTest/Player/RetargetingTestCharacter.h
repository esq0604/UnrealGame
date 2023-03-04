// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "RetargetingTestCharacter.generated.h"


class UBaseStateManagerComponent;
class UAttackComponent;
class UStatComponent;
class APlayerAttackComponent;
class APlayerStatComponent;
struct FDamageEvent;
UCLASS(config=Game)
class ARetargetingTestCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

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

	UFUNCTION(BlueprintCallable)
	void JumpAndDodge();
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Attack(const FInputActionValue& Value);

	virtual void PostInitializeComponents() override;
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

	void Sprint(const FInputActionValue& Value);
private:
	
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	
protected:
	UPROPERTY(VisibleInstanceOnly,BlueprintReadWrite,Category="Animation")
	class UCharaterAnimInstance* mAnimInstance;

	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess=true))
	class UFloatingCombatTextComponent* FloatingTextComponent;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* mHPWidgetComponent;
	UPROPERTY(EditAnywhere)
	class UPlayerHPWidget* HPBarWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Component")
	UBaseStateManagerComponent* StateManagerComponent;
	UPROPERTY(VisibleInstanceOnly,BlueprintReadWrite,Category=Move,meta=(AllowPrivateAccess=true))
	bool IsMoving;
	UPROPERTY(VisibleInstanceOnly,BlueprintReadWrite,Category=Move,meta=(AllowPrivateAccess=true))
	bool IsDodge;
	
	
private:
	UPROPERTY(VisibleInstanceOnly,Category="Component")
	class UPlayerStatComponent* StatComponent;
	
	UPROPERTY()
	bool bEnableAttackCollision;

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

	bool IsSprint;


	//Test
	UPROPERTY(BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UAnimMontage* DodgeMontage;
};

