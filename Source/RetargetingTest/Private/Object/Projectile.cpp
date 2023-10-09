// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Projectile.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	
}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CapsuleComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnComponentHitDelegateFunction);

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/**
 * 컴포넌트 히트시 화살을 부착시키도록합니다.
 */
void AProjectile::OnComponentHitDelegateFunction(UPrimitiveComponent* HitComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//화살부착
	ProjectileMovementComp->ProjectileGravityScale=0.f;
	AttachToActor(OtherActor,FAttachmentTransformRules::KeepRelativeTransform);

	//데미지 적용
	UAbilitySystemComponent* OtherActorAbilitySystemComponent=UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OtherActor);
	UAbilitySystemComponent* AbilitySystemComponent=UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());

	
}

void AProjectile::AttachToTarget(AActor* Actor)
{
}

