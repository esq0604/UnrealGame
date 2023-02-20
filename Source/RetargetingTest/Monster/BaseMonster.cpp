// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "Materials/Material.h"
#include "BaseMonsterAnimInstance.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "RetargetingTest/UI/MonsterWidget.h"
//#include "RetargetingTest/Management/MonsterPool.h"
// Sets default values
ABaseMonster::ABaseMonster()
	:mCurrentHp(200),mMaxHP(200),mAttackDamage(20),mSpeed(20)
{
	mHPWidgetComponent=CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	mHPWidgetComponent->SetupAttachment(RootComponent);
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetMaterial(BODY_MATERIAL_IDX,mDefaultMaterial);
	mAnimInstacne=Cast<UBaseMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	HPBarWidget = Cast<UMonsterWidget>(mHPWidgetComponent->GetWidget());
}

// Called to bind functionality to input
void ABaseMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ABaseMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	//GetMesh()->SetMaterial(BODY_MATERIAL_IDX,mDamagedMaterial);
	mCurrentHp-=DamageAmount;
	mAnimInstacne->PlayHitMontage();
	HPBarWidget->mHPProgressBar->SetPercent(GetHPRatio());
	if(mCurrentHp<=0)
	{
		Dead();
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
}

void ABaseMonster::Dead()
{
	mAnimInstacne->PlayDeadMontage();

	//TODO: 몽타주가 끝나면 실행합니다 
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

	MonsterDieDelegate.ExecuteIfBound(this);
	
}

float ABaseMonster::GetHPRatio()
{
	return (mMaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (mCurrentHp / mMaxHP); 
}
