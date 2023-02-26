// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "Materials/Material.h"
#include "BaseMonsterAnimInstance.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "Engine/DamageEvents.h"

#include "RetargetingTest/UI/MonsterHPWidget.h"
#include "RetargetingTest/Component/MonsterStatComponent.h"
//#include "RetargetingTest/Management/MonsterPool.h"
// Sets default values
ABaseMonster::ABaseMonster()
{
	mHPWidgetComponent=CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	mHPWidgetComponent->SetupAttachment(RootComponent);
	StatComponent =CreateDefaultSubobject<UMonsterStatComponent>(TEXT("StatComponent"));
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

void ABaseMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	mAnimInstacne = Cast<UBaseMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	mAnimInstacne->OnDoDamage.AddUObject(this,&ABaseMonster::AttackCheck);
	StatComponent->OnHPIsZero.AddLambda([this]()->void
	{
		mAnimInstacne->PlayDeadMontage();
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);
		
		//몬스터가 죽으면 풀에 넣도록 몬스터 풀의 InputMonsterToPool과 바인딩 되어 있습니다.
		MonsterDieDelegate.ExecuteIfBound(this);
	});
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	mAnimInstacne=Cast<UBaseMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	HPBarWidget = Cast<UMonsterHPWidget>(mHPWidgetComponent->GetWidget());
	HPBarWidget->BindMonsterStat(StatComponent);
}




// Called to bind functionality to input
void ABaseMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ABaseMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	mAnimInstacne->PlayHitMontage();
	
	StatComponent->GetDamaged(DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
}

void ABaseMonster::Dead()
{
	mAnimInstacne->PlayDeadMontage();

	//TODO: 몽타주가 끝나면 실행합니다 
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

	//몬스터가 죽으면 풀에 넣도록 몬스터 풀의 InputMonsterToPool과 바인딩 되어 있습니다.
	MonsterDieDelegate.ExecuteIfBound(this);
	
}

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


