// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Monster/Public/BaseMonster.h"

#include "Materials/Material.h"
#include "RetargetingTest/Monster/Public/BaseMonsterAnimInstance.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "Engine/DamageEvents.h"

#include "RetargetingTest/UI/Public/MonsterHPWidget.h"
#include "RetargetingTest/Component/Public/BaseMonsterStatComponent.h"

ABaseMonster::ABaseMonster()
{
	mHPWidgetComponent=CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	mHPWidgetComponent->SetupAttachment(RootComponent);
	StatComponent =CreateDefaultSubobject<UBaseMonsterStatComponent>(TEXT("StatComponent"));
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	mAnimInstacne = Cast<UBaseMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	mAnimInstacne->OnAttackHitCheckDelegate.AddUObject(this,&ABaseMonster::AttackCheck);
	StatComponent->OnHPIsZeroDelegate.AddLambda([this]()->void
	{
		mAnimInstacne->PlayDeadMontage();
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);
		
		MonsterDieDelegate.ExecuteIfBound(this);
	});
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	mAnimInstacne=Cast<UBaseMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	HPBarWidget = Cast<UMonsterHPWidget>(mHPWidgetComponent->GetWidget());
	HPBarWidget->BindActorStat(StatComponent);
}


/**
 * 몬스터의 데미지 피격 함수입니다. 피격 애니메이션을 실행하고, 체력을 감소합니다.
 * 스탯컴포넌트의 GetDamaged를 통해 Hp를 조절합니다.
 * @param DamageAmount - 받는 데미지의 양입니다. 플레이어의 공격력이 전달됩니다.
 */
float ABaseMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	mAnimInstacne->PlayHitMontage();
	StatComponent->SufferDamage(DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
}

/**
 * 몬스터의 공격 체크 함수입니다. 콜리전을 생성하며 닿은 적에게 데미지를 줍니다.
 * @warning 공격받는 대상이 TakeDamage 함수가 있는지 확인해야합니다.
 */
void ABaseMonster::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None,false,this);
	bool bResult=GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation()+GetActorForwardVector()*200.0f,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(50.0f),
		Params
	);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector()*AttackRange;
	FVector Center = GetActorLocation() + TraceVec*0.5f;
	float HalfHeight = AttackRange* 0.5f +AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Blue : FColor::Red;
	float DebugLifeTime = 3.0f;

	DrawDebugCapsule(GetWorld()
		,Center
		,HalfHeight
		,AttackRadius
		,CapsuleRot
		,DrawColor
		,false
		,DebugLifeTime
		);
#endif
	
	if(bResult)
	{
		if(HitResult.GetActor()->ActorHasTag("Player"))
		{
			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(StatComponent->GetAttackDamage(),DamageEvent,GetController(),this);
			//플러팅텍스트를 스폰합니다.
			//FText AttackDamage = FText::FromString(FString::SanitizeFloat(StatComponent->GetAttackDamage()));
			//FloatingTextComponent->AddFloatingActor(AttackDamage,HitResult.GetActor()->GetActorLocation());
		}
	}
}



