// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BossMonster.h"

#include "Blueprint/UserWidget.h"
#include "UI/MonsterGauge.h"


// Sets default values
ABossMonster::ABossMonster()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABossMonster::BeginPlay()
{
	Super::BeginPlay();
	HPBarWidget =CreateWidget<UMonsterGauge>(GetWorld(),HpWidgetClass,TEXT("hpbarWidget"));
	if(HPBarWidget.Get())
	{
		HPBarWidget->UpdateHPWidget(1.0f,1.0f);
		HPBarWidget->AddToViewport();
		ShowHpWidget(false);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("HpBarWidget not valid"));
	}
}

// Called every frame
void ABossMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABossMonster::ShowHpWidget(bool bShow)
{
	if(bShow)
	{
		HPBarWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		HPBarWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

