// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetingComponent.generated.h"

/**
 *	TODO : TargetComponent를 사용하려면 ITargeting이 있어야한다는게. 말이이상함. 너무 종속적이다.ITargeting의 내용을 TargetingComponent에 옮겨주는게 더 좋은 방법인거같다.
 *	현재 타게팅은 게임플레이어빌리티로 제작되어있음. 그래서 트레이스 관련부분도 해당 어빌리티에 존재함.
 *  그럼 지금 해당 클래스는 존재필요가 없는데,,
 *  해당 컴포넌트가 있다면 어빌리티를 실행할것도 아님.
 *  그럼 타게팅될 대상의 위젯은 몬스터에만 들고있으면되는건가. 일단 몬스터에만 들고있자.
 */

class ACharacter;
class UCameraComponent;
class AController;
class UUserWidget;

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

public:
	void SetTargetActor(AActor* NewTargetActor);
	void SetIstargeting(bool EnabledTargeting);

protected:
	
	UFUNCTION(BlueprintCallable)
	AActor* FindTarget();

	UFUNCTION(BlueprintCallable)
	void EnableLockOn();

	UFUNCTION(BlueprintCallable)
	void DisableLockOn();

	void ToggleLockOn();

	void UpdateTargetControlRotation();

	bool TargetCanBeTargeted();
private:
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
public:
	
protected:
	UPROPERTY(BlueprintReadWrite,Category="TargetingComponent | Component")
	TWeakObjectPtr<UCameraComponent> FollowCamera;

	/**
	 * Init
	 */
	UPROPERTY(BlueprintReadWrite,Category="TargetingComponent | Initialize")
	TWeakObjectPtr<ACharacter> OwnerCharacter;

	UPROPERTY(BlueprintReadWrite,Category="TargetingComponent | Initialize")
	TWeakObjectPtr<AController> OwnerController;

	UPROPERTY(BlueprintReadWrite,Category="TargetingComponent | Initialize")
	float TargetingDistance=900.0f;

	UPROPERTY(BlueprintReadWrite,Category="TargetingComponent | Initialize")
	float TargetingRadius=100.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="TargetingComponent | Initialize")
	float zOffSet= -50.f;

	float TargetRotationInterSpeed=5.f;

	TObjectPtr<AActor> TargetActor{nullptr};

	bool bIsTargeting=false;

};
