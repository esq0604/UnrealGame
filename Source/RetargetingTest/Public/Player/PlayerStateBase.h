// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "UI/PlayerHUD.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBase.generated.h"

class UBaseAttributeSet;
class UAbilitySystemComponent;
class UPlayerHUD;
struct FOnAttributeChangeData;
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

	UBaseAttributeSet* GetAttributes() const;
	void SetPlayerHUD(UPlayerHUD* NewPlayerHUD);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void HealthChange(const FOnAttributeChangeData& Data);
	void MaxHealthChange(const FOnAttributeChangeData& Data);
	void StaminaChange(const FOnAttributeChangeData& Data);
	void MaxManaChange(const FOnAttributeChangeData& Data);

public:


protected:
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY()
	UBaseAttributeSet* Attributes;

	TWeakObjectPtr<UPlayerHUD> PlayerHUD;

	FDelegateHandle HealthChangeDelegateHandle;
	FDelegateHandle MaxHealthChangeDelegateHandle;
	FDelegateHandle ManaChangeDelegateHandle;
	FDelegateHandle MaxManaChangeDelegateHandle;

};
