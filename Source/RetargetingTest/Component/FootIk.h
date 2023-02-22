// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FootIk.generated.h"

class ARetargetingTestCharacter;
USTRUCT()
struct FST_IK_TraceInfo
{
	GENERATED_BODY()
	float Offset;
	FVector ImpactLocation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RETARGETINGTEST_API UFootIk : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFootIk();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FST_IK_TraceInfo IK_FootTrace(float TraceDistance, FName Socket);
	FRotator NormalToRotator(FVector Vector);
	void IK_UpdateFootRotation(float DeltaTime,FRotator TargetVal, FRotator* FootRotatorVal, float InterpSpeed);

	void IK_Update_CapsuleHalfHeight(float fDeltaTime, float fHipsShifts, bool bResetDefault);

	void IK_Update_FootOffset(float fDeltaTime, float fTargetValue, float* fEffectorValue, float fInterpSpeed);
public:


	
private:


protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FRotator FootRotation_Left;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FRotator FootRotation_Right;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	float m_fHipOffset;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float IKCapsuleHalfHeight=90.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float FootOffset_Left;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float FootOffset_Right;
private:
	ARetargetingTestCharacter* Character;

	UPROPERTY()
	FST_IK_TraceInfo Trace_Left;
	UPROPERTY()
	FST_IK_TraceInfo Trace_Right;

	
};
