// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/CommonMonster.h"

#include "Components/WidgetComponent.h"
#include "UI/MonsterGauge.h"


// Sets default values
ACommonMonster::ACommonMonster()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidgetComponent"));
	HPWidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACommonMonster::BeginPlay()
{
	Super::BeginPlay();
	if(HPWidgetComponent->GetWidget())
	{
		HPBarWidget=Cast<UMonsterGauge>(HPWidgetComponent->GetWidget());
		if(HPBarWidget.Get())
		{
			HPBarWidget->UpdateHPWidget(1.0f,1.0f);
		}
	}
}

// Called every frame
void ACommonMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACommonMonster::ShowHpWidget(bool bShow)
{
	
}

