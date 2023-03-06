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
	UFUNCTION(BlueprintCallable)
	void SetInvincible(bool NewIsInvincible){IsInvincible=NewIsInvincible;}

	/* Getter */
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	UFUNCTION(BlueprintCallable)
	class UPlayerStatComponent* GetStatComponent() const;
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


private:
	
public:
	
	
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

	UPROPERTY(VisibleInstanceOnly,Category="Component")
	class UPlayerStatComponent* StatComponent;

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

	
	bool IsSprint;
	bool IsInvincible;
	
	UPROPERTY(BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UAnimMontage* DodgeMontage;
};

