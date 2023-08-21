// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Monster/BaseMonster.h"

#include "AbilitySystemComponent.h"
#include "Attribute/BaseAttributeSet.h"
#include "Component/WeaponCollisionComponent.h"
#include "Components/WidgetComponent.h"
#include "Materials/Material.h"
#include "Engine/DamageEvents.h"

#include "RetargetingTest/Public/Monster/BaseMonsterAnimInstance.h"
#include "UI/MonsterGauge.h"

ABaseMonster::ABaseMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	EnemyAttributesSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("AttributeSet"));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);


	HPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidgetComponent"));
	HPWidgetComponent->SetupAttachment(RootComponent);

	WeaponCollisionComponent=CreateDefaultSubobject<UWeaponCollisionComponent>(TEXT("WeaponCollisionComponent"));

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
	InitializeAttributes();
	GiveDefaultAbilities();
}

void ABaseMonster::ToggleWeaponCollision_Implementation(bool IsEnable)
{
	WeaponCollisionComponent->SetCollisionEnable(IsEnable);
}

UAnimMontage* ABaseMonster::GetHitReaction_Implementation(EHitDirection HitDirection)
{
	switch (HitDirection)
	{
	case EHitDirection::Forward:
		return ForwardHitReaction;
	case EHitDirection::Backward:
		return BackWardHitReaction;
	case EHitDirection::Left:
		return LeftHitReaction;
	case EHitDirection::Right:
		return RightHitReaction;
	default:
		return nullptr;
	}
}


/**
 * 몬스터마다 HPBarWidget은 존재하나. WidgetComponent는 일반몬스터에만 존재합니다(몬스터의 위에 체력바를 보여주기 위하여). 
 */
void ABaseMonster::HealthChange(const FOnAttributeChangeData& Data)
{
	if(Data.NewValue>=0.0f)
	{
		const float NewHealthPercent=(Data.NewValue/EnemyAttributesSet->GetMaxHealth());
		const float OldHealthPercent=Data.OldValue/EnemyAttributesSet->GetMaxHealth();
	
		HPBarWidget->UpdateHPWidget(NewHealthPercent,OldHealthPercent);

		if(HPWidgetComponent)
		{
			HPWidgetComponent->UpdateWidget();
		}
		// if(EnemyAttributesSet->GetHealth()<=0)
		// {
		// 	SetActorHiddenInGame(true);
		// 	SetActorEnableCollision(false);
		// 	SetActorTickEnabled(false);
		// 	//MonsterDieDelegate.Execute(this);
		// }
	}
	else
	{
		
	}

}

TObjectPtr<UBehaviorTree> ABaseMonster::GetBehaviorTree() const
{
	return BehaviorTree;
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	if(!EnemyAttributesSet)
	{
		UE_LOG(LogTemp,Warning,TEXT("Attributes not vaild"));
	}
	if(AbilitySystemComponent)
	{
		if(EnemyAttributesSet)
		{
			HealthChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EnemyAttributesSet->GetHealthAttribute()).AddUObject(this,&ABaseMonster::HealthChange);
		}
	}
	
	if(HPWidgetComponent)
	{
		if(HPWidgetComponent->GetWidget())
		{
			HPBarWidget=Cast<UMonsterGauge>(HPWidgetComponent->GetWidget());
		}
	}
	else
	{
		//HPBarWidget=Cast<UMonsterGauge>(CreateWidget(GetController(),HpWidgetClass));
	}
	
	if(HPBarWidget.IsValid())
	{
		HPBarWidget->UpdateHPWidget(1.0f,1.0f);
	}
	mAnimInstacne=Cast<UBaseMonsterAnimInstance>(GetMesh()->GetAnimInstance());
}

/**
 * 몬스터의 데미지 피격 함수입니다. 피격 애니메이션을 실행하고, 체력을 감소합니다.
 * 스탯컴포넌트의 GetDamaged를 통해 Hp를 조절합니다.
 * @param DamageAmount - 받는 데미지의 양입니다. 플레이어의 공격력이 전달됩니다.
 */
float ABaseMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
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
				FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());  
			}
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Post Initialize AbilityComp not vaild"));
	}
}

void ABaseMonster::GiveDefaultAbilities()
{
	if(AbilitySystemComponent)
	{
		//GiveAbility called with an invalid Ability Class
		for(TSubclassOf<UGameplayAbility>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(),1,0));
		}
	}
}

UAbilitySystemComponent* ABaseMonster::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

/**
 * 스포너에 의해 스폰될때 체력을 다시 max health양으로 초기화합니다.
 */
void ABaseMonster::SpawnInit()
{
	EnemyAttributesSet->SetHealth(EnemyAttributesSet->GetMaxHealth());
}





