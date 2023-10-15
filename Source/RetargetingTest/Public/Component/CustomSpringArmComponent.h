// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "CustomSpringArmComponent.generated.h"

UENUM(BlueprintType)
enum class EDirection : uint8
{
	Left	UMETA(DisplayName = "Left"),
	Right	UMETA(DisplayName = "Right"),
};
class UTargetingComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UCustomSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

public:
	UCustomSpringArmComponent();

	/* Max Distance from the character for an actor to be targetable */
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
	float MaxTargetLockDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
	bool bUseSoftLock;

	/* Turn debug visuals on/off */
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
	bool bDrawDebug;

	/* True if lock was recently broken and mouse delta is still high */
	bool bSoftlockRequiresReset;

	/* The component the camera is currently locked on to */
	UPROPERTY(BlueprintReadOnly)
	UTargetingComponent* CameraTarget;


	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ToggleCameraLock();
	void ToggleSoftLock();
	void LockToTarget(UTargetingComponent* NewTargetComponent);
	void BreakTargetLock();
	class UTargetingComponent* GetLockTarget();
	void SwitchTarget(EDirection SwitchDirection);
	TArray<UTargetingComponent*> GetTargetComponents();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Lock On Camera")
		bool IsCameraLockedToTarget();
	
};
