// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatComponent.h"
#include "Components/ActorComponent.h"
#include "BasePlayerStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnStaminaChangedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UBasePlayerStatComponent : public UBaseStatComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBasePlayerStatComponent();
	void SetStamina(float NewStamina);
	float GetCurrentStamina() const;
	float GetCurrentStaminaPercent() const;
	float GetCalculateStaminaRatio(float ChangedStamina) const;

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	FOnStaminaChangedSignature OnStaminaChangedDelegate;
protected:
    float MaxStamina=100.0f;
	float CurrentStamina = MaxStamina;
	float CurStaminaPercent;
	float RegenStamina=1.0f;
	const float StaminaRegenerateValue=0.02f;

private:

};
