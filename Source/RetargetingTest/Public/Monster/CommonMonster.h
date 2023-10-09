// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonster.h"
#include "CommonMonster.generated.h"

UCLASS()
class RETARGETINGTEST_API ACommonMonster : public ABaseMonster
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACommonMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ShowHpWidget(bool bShow) override final;


private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="EnemyBase | Component")
	TObjectPtr<UWidgetComponent> HPWidgetComponent;
};
