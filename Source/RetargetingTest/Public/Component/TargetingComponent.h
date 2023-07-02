// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetingComponent.generated.h"

class ACharacter;
class UCameraComponent;
class AController;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTargetingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	AActor* FindTarget();
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void RotateToTarget();
public:
	UPROPERTY(BlueprintReadWrite,Category="TargetingComponent | Initialize")
	float TargetingDistance=900.0f;
	UPROPERTY(BlueprintReadWrite,Category="TargetingComponent | Initialize")
	float TargetingRadius=100.0f;
protected:
	UPROPERTY(BlueprintReadWrite,Category="TargetingComponent | Component")
	TWeakObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(BlueprintReadWrite,Category="TargetingComponent | Initialize")
	TWeakObjectPtr<ACharacter> OwnerCharacter;

	UPROPERTY(BlueprintReadWrite,Category="TargetingComponent | Initialize")
	TWeakObjectPtr<AController> OwnerController;

	
	bool bIsTargeting;

};
