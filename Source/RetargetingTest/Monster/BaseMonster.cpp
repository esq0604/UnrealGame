// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "Materials/Material.h"
#include "BaseMonsterAnimInstance.h"
//#include "RetargetingTest/Management/MonsterPool.h"
// Sets default values
ABaseMonster::ABaseMonster()
	:mHp(50),mAttackDamage(20),mSpeed(20)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetMaterial(BODY_MATERIAL_IDX,mDefaultMaterial);
	mAnimInstacne=Cast<UBaseMonsterAnimInstance>(GetMesh()->GetAnimInstance());
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
	mHp-=DamageAmount;
	if(mHp<=0)
	{
		Dead();
	}
	mAnimInstacne->PlayHitMontage();
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

}

void ABaseMonster::Dead()
{
	mAnimInstacne->PlayDeadMontage();
	
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

	MonsterDieDelegate.ExecuteIfBound(this);
	
}
