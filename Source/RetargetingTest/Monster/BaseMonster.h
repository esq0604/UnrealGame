// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseMonster.generated.h"

class USkeletalMeshComponent;

UCLASS()
class RETARGETINGTEST_API ABaseMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void GetDamaged(float Damage);
private:
    UPROPERTY(VisibleAnywhere, Category="Monster | Stat", meta=(AllowPrivateAccess="true"))
	float mHp;

	UPROPERTY(VisibleAnywhere, Category="Monster | Stat")
	float mAttackDamage;

	UPROPERTY(VisibleAnywhere, Category="Monster | Stat")
	float mSpeed;

	USkeletalMeshComponent* mSkeletalMeshComp;
};
