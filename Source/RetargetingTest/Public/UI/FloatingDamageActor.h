// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingDamageActor.generated.h"

class UFloatingTextWidget;
class UWidgetComponent;

UCLASS()
class RETARGETINGTEST_API	AFloatingDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingDamageActor();

	UFUNCTION(BlueprintImplementableEvent)
	void Initialize(const FText& Text);
	//액터와 시작시 필요한 정보를 초기화합니다.
	UFUNCTION(BlueprintNativeEvent)
	void InitSpawnDeferred();
	UFUNCTION()
	void InitSpawnDeferred_Implementation();
	FORCEINLINE const FVector& GetAnchorLocation() const {return AnchorLocation;}

	// UFUNCTION()
	// void HandleAnimFinished();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AnimFinishedDelegateFunction();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UWidgetComponent* DamageWidgetComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	TSubclassOf<UFloatingTextWidget> DamageTextWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> DamageTextWidget;
	
	FVector AnchorLocation;
};
