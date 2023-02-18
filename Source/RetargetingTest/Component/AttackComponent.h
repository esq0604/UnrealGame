// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAttackComponent();

	UFUNCTION(BlueprintCallable)
	void EnableCollision();

	UFUNCTION(BlueprintCallable)
	void DisalbeCollsion();

	UFUNCTION(BlueprintCallable)
	void TakeDamage();
	// UFUNCTION(BlueprintCallable)
	// void OnAttackCollisionOverlap(class UPrimitiveComponent* OverlappedComponent);	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	virtual void BeginPlay() override;

private:
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attack",meta=(AllowPrivateAccess=true))
	// class UBoxComponent* mAttackCollision;
	
public:
	UPROPERTY(VisibleAnywhere)
	float mDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attack",meta=(AllowPrivateAccess=true))
	class UAttackCollision* mAttackCollision;

};
