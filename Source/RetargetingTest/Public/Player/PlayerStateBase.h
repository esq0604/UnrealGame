// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Attribute/RuneAttributeSet.h"
#include "UI/PlayerHUD.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBase.generated.h"

class UAbilitySystemComponent;
class URuneAttributeSet;
class UPlayerHUD;
UCLASS()
class RETARGETINGTEST_API APlayerStateBase : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerStateBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	URuneAttributeSet* GetAttributes() const;
	void SetPlayerHUD(UPlayerHUD* NewPlayerHUD);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HealthChange(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChange(const FOnAttributeChangeData& Data);
	virtual void StaminaChange(const FOnAttributeChangeData& Data);
	virtual void MaxManaChange(const FOnAttributeChangeData& Data);

public:


protected:
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY()
	URuneAttributeSet* Attributes;

	TWeakObjectPtr<UPlayerHUD> PSPlayerHUD;

	FDelegateHandle HealthChangeDelegateHandle;
	FDelegateHandle MaxHealthChangeDelegateHandle;
	FDelegateHandle StaminaChangeDelegateHandle;
	FDelegateHandle MaxManaChangeDelegateHandle;
	FDelegateHandle CharacterLevelChangeDelegateHandle;

};
