// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "Materials/Material.h"
#include "BaseMonsterAnimInstance.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "RetargetingTest/UI/MonsterWidget.h"
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
	HPBarWidget = Cast<UMonsterWidget>(mHPWidgetComponent->GetWidget());
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


