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

//TODO : CharacterBase 클래스이므로, 플레이어 클래스를 따로 나누어 CharacterBase에 존재하는 Player 속성들을 옮겨야합니다.
UCLASS(config=Game)
class ACharacterBase : public ACharacter, public IAbilitySystemInterface
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
protected:
	virtual void PostInitializeComponents() override;

	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;
public:
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TArray<AItemBase*> Inventory;
protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Animation")
	UCharaterAnimInstance* mAnimInstance;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	UFloatingCombatTextComponent* FloatingTextComponent;

private:
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<URuneAttributeSet> Attributes;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Component",meta=(AllowPrivateAccess="true"))
	UMotionWarpingComponent* MotionWarpComponent;


	class UInventoryManagerComponent* InventoryManagerComponent;


};
