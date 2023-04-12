// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class UPDAWeapon;
class ACharacter;
UCLASS()
class RETARGETINGTEST_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void CreateWeaponStateAndAbility();
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Data Asset")
	UPDAWeapon* WeaponDataAsset;

};
