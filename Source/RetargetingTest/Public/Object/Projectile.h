// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UCapsuleComponent;
class UProjectileMovementComponent;
UCLASS()
class RETARGETINGTEST_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION(BlueprintCallable)
	void OnComponentHitDelegateFunction(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION(BlueprintCallable)
	void AttachToTarget(AActor* Actor);
private:
	UPROPERTY(EditDefaultsOnly,Category="Component")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComp;
	UPROPERTY(EditDefaultsOnly,Category="Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(EditDefaultsOnly,Category="Component")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	
};
