// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoCharacterBase.h"
#include "GameplayTagContainer.h"
#include "DemoCharacter.generated.h"

struct FGameplayTag;
class ADemoPlayerState;
class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API ADemoCharacter : public ADemoCharacterBase
{
	GENERATED_BODY()

public:
	ADemoCharacter(const class FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	USpringArmComponent* GetCameraBoom();

	UCameraComponent* GetFollowCamera();

	UFUNCTION(BlueprintCallable,Category="Demo|Camera")
	float GetStartingCameraBoomArmLength();

	UFUNCTION(BlueprintCallable,Category="Demo|Camera")
	FVector GetStartingCameraBoomArmLocation();

protected:
	virtual void BeginPlay() override;
	
	void LookUp(float Value);

	void LookUpRate(float Value);

	void Turn(float Value);

	void TurnRate(float Value);

	void MoveForward(float Value);

	void MoveRight(float Value);

	virtual void OnRep_PlayerState() override;
	
	void InitializeStartingValues(ADemoPlayerState* PS);

	void BindAscInput();
protected:
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Demo|Camera")
	float BaseTurnRate = 45.0f;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Demo|Camera")
	float BaseLookUpRate = 45.0f;
	UPROPERTY(BlueprintReadOnly,Category="Demo|Camera")
	float StartingCameraBoomArmLength;
	
	UPROPERTY(BlueprintReadOnly,Category="Demo|Camera")
	FVector StartingCameraBoomArmLocation;
	
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category="Demo|Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category="Demo|Camera")
	UCameraComponent* FollowCamera;
	
	bool ASCInputBound=false;
	FGameplayTag DeadTag;

	
};
