// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponCollisionComponent.generated.h"

struct FGameplayEventData;

DECLARE_DELEGATE_TwoParams(FOnHitSignature,FGameplayEventData&, const FHitResult&)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UWeaponCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponCollisionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void SetWeaponStart(FName WeaponStart);
	
	UFUNCTION(BlueprintCallable)
	void SetWeaponEnd(FName WeaponEnd);

	UFUNCTION(BlueprintCallable)
	void SetCollisionEnable(bool CollisionEnable);

	UFUNCTION(BlueprintCallable)
	void SetCollisionMeshComp(UPrimitiveComponent* CollisionMesh);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void CollisionEnable();	
	bool CanHitActor(AActor* CheckActor);

public:
	FOnHitSignature OnHitDelegate;

protected:
	//	Draw Trace 
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Collision|Initialize")
	float mTraceRadius{20.f};
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Collision|Initialize")
	float mDebugTime{5.0f};
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Collision|Initialize")
	FName mWeaponStartName;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Collision|Initialize")
	FName mWeaponEndName;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Collision|Initialize")
	TArray<AActor*> mTraceActorToIgnore;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Collision|Initialize")
	TObjectPtr<UPrimitiveComponent> mCollisionMeshComponent;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Collision|Initialize")
	TArray<TEnumAsByte<EObjectTypeQuery>> mTraceObjectType;
	FHitResult LastHit;

private:
	//	Collision Enable
	bool mCollisionEnable;
	//	Check Trace Actor
	TArray<AActor*> AlreadyHitActor;
	
};
