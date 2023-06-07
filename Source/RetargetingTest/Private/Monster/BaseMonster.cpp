// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Monster/BaseMonster.h"

#include "AbilitySystemComponent.h"
#include "Attribute/EnemyAttributeSetBase.h"
#include "Components/WidgetComponent.h"
#include "Materials/Material.h"
#include "Engine/DamageEvents.h"

#include "RetargetingTest/Public/Monster/BaseMonsterAnimInstance.h"
#include "UI/MonsterGauge.h"

ABaseMonster::ABaseMonster()
{
//	HPWidgetComponent=CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
//	HPWidgetComponent->SetupAttachment(RootComponent);
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<UEnemyAttributeSetBase>(TEXT("Attribute"));

	HPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidgetComponent"));
	
}

/**
 * 애님인스턴스와, 스탯컴포넌트의 델리게이트에 바인딩됩니다.
 * 애님인스턴스 - 공격체크 함수와 바인딩합니다.
 * 스탯컴포넌트 - 체력이 없을시에 대한 동작을 람다로 지정합니다.
 * @warning 몬스터가 죽으면 본인을 풀에 넣도록 몬스터 풀의 InputMonsterToPool과 바인딩 되어 있습니다.
 */
void ABaseMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp,Warning,TEXT("Default Attribute, Default Ability Init"));
	InitializeAttributes();
	GiveDefaultAbilities();
}

void ABaseMonster::HealthChange(const FOnAttributeChangeData& Data)
{
	const float NewHealthPercent=(Data.NewValue/Attributes->GetMaxHealth());
	const float OldHealthPercent=Data.OldValue/Attributes->GetMaxHealth();
	HPBarWidget->UpdateHPWidget(NewHealthPercent,OldHealthPercent);
	HPWidgetComponent->UpdateWidget();
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	if(AbilitySystemComponent)
	{
		HealthChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute()).AddUObject(this,&ABaseMonster::HealthChange);
	}
	//HPBarWidget=Cast<UMonsterGauge>(CreateWidget(this,HPBarWidgetClass));
	//HPBarWidget->AddToViewport();
	//HPBarWidget->UpdateHPWidget(Attributes->GetHealth()/Attributes->GetMaxHealth(),Attributes->GetHealth()/Attributes->GetMaxHealth());
	HPWidgetComponent->SetWidgetClass(HPBarWidgetClass);
	HPWidgetComponent->SetVisibility(true);
	HPBarWidget=Cast<UMonsterGauge>(HPWidgetComponent->GetWidget());
	HPBarWidget->UpdateHPWidget(1.0f,1.0f);
}

/**
 * 몬스터의 데미지 피격 함수입니다. 피격 애니메이션을 실행하고, 체력을 감소합니다.
 * 스탯컴포넌트의 GetDamaged를 통해 Hp를 조절합니다.
 * @param DamageAmount - 받는 데미지의 양입니다. 플레이어의 공격력이 전달됩니다.
 */
float ABaseMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	AnimInstacne->PlayHitMontage();
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ABaseMonster::InitializeAttributes()
{
	if(AbilitySystemComponent)
	{
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);

		for(const TSubclassOf<UGameplayEffect>& GameplayEffect : DefaultAttributeEffects)
		{
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect,1,EffectContextHandle);

			if(SpecHandle.IsValid())
			{
				UE_LOG(LogTemp,Warning,TEXT("InitAttribute"));
				FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());  
			}
		}
	}
}

void ABaseMonster::GiveDefaultAbilities()
{
	if(AbilitySystemComponent)
	{
		for(TSubclassOf<UGameplayAbility>& StartupAbility : DefaultAbilities)
		{
			UE_LOG(LogTemp,Warning,TEXT("GiveDefaultAbility"));
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(),1,0));
		}
	}
}

UAbilitySystemComponent* ABaseMonster::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}




