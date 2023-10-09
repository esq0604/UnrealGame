// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/FloatingDamageActor.h"

#include <string>

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Attribute/BaseAttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "UI/FloatingTextWidget.h"

// Sets default values
AFloatingDamageActor::AFloatingDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;;
	
	DamageWidgetComponent=CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageTextWidget"));
	SetRootComponent(DamageWidgetComponent);
	//TSoftClassPtr<AActor> CombatTextBpClass = TSoftClassPtr<AActor>(FSoftObjectPath(TEXT("Blueprint'/GameContent/Blueprint/UI/Widgets/Modals/WBP_CombatText.WBP_CombatText_C'")));

	// static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("WidgetBlueprint'/Game/Content/Blueprint/UI/Widgets/Modals/WBP_CombatText.WBP_CombatText'_C"));
	// if(UW.Succeeded())
	// {
	// 	DamageWidgetComponent->SetWidgetClass(UW.Class);
	// }
	// else
	// {
	// 	UE_LOG(LogTemp,Warning,TEXT("not found"));
	// }

}

/**
 * SpawnDeffered로 생성되기 이전 초기화입니다. 위젯생성, 데미지텍스트설정, 위젯애니메이션바인딩이 이루어집니다.
 */
void AFloatingDamageActor::InitSpawnDeferred_Implementation()
{
	// UUserWidget* Widget = DamageWidgetComponent->GetUserWidgetObject();
	// UFloatingTextWidget* DamageTextWidget=Cast<UFloatingTextWidget>(Widget);
	//
	UE_LOG(LogTemp,Warning,TEXT("Before Spawn Init"));
	DamageTextWidget = CreateWidget(GetWorld(),DamageTextWidgetClass,TEXT("FloatingDamage"));
	DamageWidgetComponent->SetWidget(DamageTextWidget);
	DamageWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	DamageTextWidget = DamageWidgetComponent->GetWidget();
	UAbilitySystemComponent* OwnerAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());


	//플레이어의 데미지 속성을가져와 텍스트를 지정합니다.
	const UAttributeSet* OwnerAttributeSet= OwnerAbilitySystem->GetAttributeSet(UBaseAttributeSet::StaticClass());
	const UBaseAttributeSet* BaseAttributeSet = Cast<UBaseAttributeSet>(OwnerAttributeSet);
	const FText DamageText =FText::AsNumber(BaseAttributeSet->GetDamage());
	
	UFloatingTextWidget* FloatingDamageTextWidget =Cast<UFloatingTextWidget>(DamageTextWidget);
	if(FloatingDamageTextWidget)
	{
		FloatingDamageTextWidget->SetDamageText(DamageText);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("FloatingDamageTextWidget nullptr"));
	}
	
	//애닝메이션과 바인딩을합니다.
	//FloatingDamageTextWidget->AnimFinishedDelegateForActor.BindDynamic(this,&AFloatingDamageActor::AnimFinishedDelegateFunction);
}


// void AFloatingDamageActor::HandleAnimFinished()
// {
// 	Destroy();
// }

// Called when the game starts or when spawned
void AFloatingDamageActor::BeginPlay()
{
	Super::BeginPlay();
	SetRootComponent(DamageWidgetComponent);
	AnchorLocation=GetActorLocation();
}

void AFloatingDamageActor::AnimFinishedDelegateFunction()
{
	UE_LOG(LogTemp,Warning,TEXT("Destory Actor"));
	Destroy();
}

// Called every frame
void AFloatingDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

