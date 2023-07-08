// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Monster/BaseMonster.h"

#include "AbilitySystemComponent.h"
#include "Attribute/BaseAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Materials/Material.h"
#include "Engine/DamageEvents.h"

#include "RetargetingTest/Public/Monster/BaseMonsterAnimInstance.h"
#include "UI/MonsterGauge.h"
#include "Weapon/EHitReaction.h"

ABaseMonster::ABaseMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Attributes = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("Attribute"));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);


	HPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidgetComponent"));
	HPWidgetComponent->SetupAttachment(RootComponent);



}

/**
 * 애님인스턴스와, 스탯컴포넌트의 델리게이트에 바인딩됩니다.
 * 애님인스턴스 - 공격체크 함수와 바인딩합니다.
 * 스탯컴포넌트 - 체력이 없을시에 대한 동작을 람다로 지정합니다.
 * @warning 몬스터가 죽으면 본인을 풀에 넣도록 몬스터 풀의 InputMonsterToPool과 바인딩 되어 있습니다.
 */
void ABaseMonster::PostInitializeComponents()
{
	UE_LOG(LogTemp,Warning,TEXT("PostInitComp"));
	Super::PostInitializeComponents();
	InitializeAttributes();
	GiveDefaultAbilities();
}


/**
 * 몬스터마다 HPBarWidget은 존재하나. WidgetComponent는 일반몬스터에만 존재합니다(몬스터의 위에 체력바를 보여주기 위하여). 
 */
void ABaseMonster::HealthChange(const FOnAttributeChangeData& Data)
{
	const float NewHealthPercent=(Data.NewValue/Attributes->GetMaxHealth());
	const float OldHealthPercent=Data.OldValue/Attributes->GetMaxHealth();
	
	HPBarWidget->UpdateHPWidget(NewHealthPercent,OldHealthPercent);

	if(HPWidgetComponent)
	{
		HPWidgetComponent->UpdateWidget();
	}
	if(Attributes->GetHealth()<=0)
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);
		MonsterDieDelegate.Execute(this);
	}
}
//
// AActor* ABaseMonster::GetHitActor_Implementation()
// {
// 	return mHitActor;
// }
//
// void ABaseMonster::SetHitActor_Implementation(AActor* HitActor)
// {
// 	mHitActor=HitActor;
// }
//
// EHitReaction ABaseMonster::GetHitReaction_Implementation()
// {
// 	return mHitReaction;
// }
//
// void ABaseMonster::SetHitReaction_Implementation(EHitReaction HitReaction)
// {
// 	mHitReaction=HitReaction;
// }

void ABaseMonster::AttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// mHitActor=OtherActor;
	// if(Attributes)
	// {
	// 	const float Damage = Attributes->GetDamage();
	// 	UGameplayStatics::ApplyDamage(OtherActor,Damage,GetController(),nullptr,nullptr);
	//
	// 	const FVector HitActorForwardVector = OtherActor->GetActorForwardVector();
	// 	const FVector ActorForwardVector = GetActorForwardVector();
	//
	// 	const auto Direction =FVector::DotProduct(HitActorForwardVector,ActorForwardVector);
	//
	// 	if(Direction>=0.0f)
	// 	{
	// 		mHitReaction = EHitReaction::Backward;
	// 	}
	// 	else
	// 	{
	// 		mHitReaction= EHitReaction::Forward;
	// 	}
	// }
}



TObjectPtr<UBehaviorTree> ABaseMonster::GetBehaviorTree() const
{
	return BehaviorTree;
}

// void ABaseMonster::OnTargetSet(TWeakObjectPtr<AActor> NewTarget)
// {
// 	TargetActor=NewTarget.Get();
// }



// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	InitializeAttributes();
	GiveDefaultAbilities();
	if(!Attributes)
	{
		UE_LOG(LogTemp,Warning,TEXT("Attributes not vaild"));
	}
	if(AbilitySystemComponent)
	{
		if(Attributes)
		{
			HealthChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute()).AddUObject(this,&ABaseMonster::HealthChange);
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
}

void ABaseMonster::GiveDefaultAbilities()
{
	if(AbilitySystemComponent)
	{
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


// void ABaseMonster::ToggleWeaponCollision_Implementation(bool bIsEnable)
// {
// 	// if(AttackCollision->GetCollisionEnabled()==ECollisionEnabled::QueryAndPhysics)
// 	// {
// 	// 	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
// 	// }
// 	// else
// 	// {
// 	// 	UE_LOG(LogTemp,Warning,TEXT("Collision Enabled"));
// 	// 	AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
// 	// }
// }

/**
 * 스포너에 의해 스폰될때 체력을 다시 maxhealth양으로 초기화합니다.
 */
void ABaseMonster::SpawnInit()
{
	Attributes->SetHealth(Attributes->GetMaxHealth());
}





