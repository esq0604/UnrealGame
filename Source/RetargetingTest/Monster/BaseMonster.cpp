// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "Materials/Material.h"
// Sets default values
ABaseMonster::ABaseMonster()
	:mHp(500),mAttackDamage(20),mSpeed(20)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mSkeletalMeshComp=GetMesh();
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MonsterMesh(TEXT("/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin"));
	if(MonsterMesh.Object != nullptr)
	mSkeletalMeshComp->SetSkeletalMeshAsset(MonsterMesh.Object);
	mSkeletalMeshComp->SetRelativeLocationAndRotation(FVector(0.0f,0.0f,-90.0f),FRotator(0.0f,-90.0f,0.0f));
	
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFinder(TEXT("/Game/StarterContent/Materials/M_Metal_Gold"));
	if(MaterialFinder.Succeeded())
	{
		mSkeletalMeshComp->SetMaterial(BODY_MATERIAL_IDX,MaterialFinder.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UMaterial> DamagedMaterial(TEXT("/Game/StarterContent/Materials/M_Ground_Moss"));
	if(DamagedMaterial.Succeeded())
		mDamagedMaterial=DamagedMaterial.Object;
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseMonster::GetDamaged(float Damaged)
{
	//mHp-=Damaged;
	//mSkeletalMeshComp->SetMaterial(BODY_MATERIAL_IDX,mDamagedMaterial);
}

float ABaseMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	mSkeletalMeshComp->SetMaterial(BODY_MATERIAL_IDX,mDamagedMaterial);

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

