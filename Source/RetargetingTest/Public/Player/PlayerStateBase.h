// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBase.generated.h"

class UAbilitySystemComponent;
class URuneAttributeSet;

UCLASS()
class RETARGETINGTEST_API APlayerStateBase : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerStateBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	URuneAttributeSet* GetAttributes() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
	URuneAttributeSet* Attributes;
	
};
