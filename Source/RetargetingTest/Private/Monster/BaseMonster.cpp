// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Monster/BaseMonster.h"

#include "AbilitySystemComponent.h"
#include "MotionWarpingComponent.h"
#include "Attribute/BaseAttributeSet.h"
#include "Component/WeaponCollisionComponent.h"
#include "Components/WidgetComponent.h"
#include "Materials/Material.h"

#include "RetargetingTest/Public/Monster/BaseMonsterAnimInstance.h"
#include "UI/MonsterGauge.h"
#include "Object/BaseWeaponInstance.h"

ABaseMonster::ABaseMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	EnemyAttributesSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("AttributeSet"));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	TargetWidgetComponent=CreateDefaultSubobject<UWidgetComponent>(TEXT("TargetWidgetComponent"));
	TargetWidgetComponent->SetupAttachment(GetMesh());

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpComp"));
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
	//ICombat::ToggleWeaponCollision_Implementation(IsEnable);
	WeaponInstance->GetCollisionComponent()->SetCollisionEnable(IsEnable);
}

UAnimMontage* ABaseMonster::GetHitReaction_Implementation(EHitDirection HitDirection)
{
	//ICombat::GetHitReaction_Implementation(HitDirection);
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

UAnimMontage* ABaseMonster::GetParryMontage_Implementation(EHitDirection HitDirection)
{
	return nullptr;
}

bool ABaseMonster::CanReceivedDamaged_Implementation()
{
	UE_LOG(LogTemp,Warning,TEXT("Implementation BlueprintFunction"));
	return false;
}

void ABaseMonster::SetIFrame_Implementation(bool bEnabled)
{
	bIFrame=bEnabled;
}

void ABaseMonster::OnTargeted_Implementation(bool bIsTargeted)
{
	TargetWidgetComponent->SetVisibility(bIsTargeted);
}

bool ABaseMonster::CanBeTargeted_Implementation()
{
	return true;
}

void ABaseMonster::MotionWarpForwardToDistance(float MoveDistance)
{
	const FVector CurLocation = GetActorLocation();
	const FVector ForwardVec  = GetActorForwardVector();

	const FVector TargetLoc = GetActorLocation() + (GetActorForwardVector() * MoveDistance);

	MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(TEXT("Warp"),TargetLoc);
}


/**
 * 몬스터마다 HPBarWidget은 존재하나. WidgetComponent는 일반몬스터에만 존재합니다(몬스터의 위에 체력바를 보여주기 위하여). 
 */
void ABaseMonster::HealthChange(const FOnAttributeChangeData& Data)
{
	if(HPBarWidget.Get())
	{
		if(Data.NewValue <= 0.f)
		{
			// 죽음 설정
			HPBarWidget->UpdateHPWidget(0.f,0.f);
			DoDead();
		}
		else
		{
			const float NewHealthPercent=(Data.NewValue/EnemyAttributesSet->GetMaxHealth());
			const float OldHealthPercent=Data.OldValue/EnemyAttributesSet->GetMaxHealth();
		
			HPBarWidget->UpdateHPWidget(NewHealthPercent,OldHealthPercent);
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Hp bar widget null in basemonster"));
	}
}

UBehaviorTree* ABaseMonster::GetBehaviorTree() const
{
	return BehaviorTreeAsset;
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	
		
	HealthChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EnemyAttributesSet->GetHealthAttribute()).AddUObject(this,&ABaseMonster::HealthChange);
	mAnimInstacne=Cast<UBaseMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	

	
	TargetWidgetComponent->SetWidgetClass(TargetWidgetClass);
	TargetWidgetComponent->SetVisibility(false);
	
	// Weapon 클래스로 Weapon을 스폰 및 무기가 가지고 있는 어빌리티를 추가해줍니다.
	if(WeaponClass)
	{
		const FActorSpawnParameters SpawnInfo;
		WeaponInstance=GetWorld()->SpawnActor<ABaseWeaponInstance>(WeaponClass,GetActorLocation(),GetActorRotation(),SpawnInfo);
		WeaponInstance->SetOwner(this);
		WeaponInstance->AddAbilities();
		WeaponInstance->OnEquipped(this);
	}
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
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(),1,0,this));
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





