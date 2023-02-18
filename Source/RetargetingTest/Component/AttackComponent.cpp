// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "Components/BoxComponent.h"
#include "RetargetingTest/Player/RetargetingTestCharacter.h"
#include "AttackCollision.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
	:mDamage(30.0f)
{

	mAttackCollision= CreateDefaultSubobject<UAttackCollision>(TEXT("AttackCollision"));
	//mAttackCollision->OnComponentBeginOverlap.AddDynamic(this,&UAttackComponent::OnOverlapBegin);

	mAttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mAttackCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	if(mAttackCollision)
	{
		mAttackCollision->AttachToComponent(GetOwner()->GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
		mAttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}
}

void UAttackComponent::EnableCollision()
{
	if(mAttackCollision)
	{
		ARetargetingTestCharacter* Character=Cast<ARetargetingTestCharacter>(GetOwner());
		//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green,TEXT("%s"),Character);
		mAttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		FHitResult HitResult;
		FCollisionQueryParams Params(NAME_None,false,Cast<ARetargetingTestCharacter>(GetOwner()));
		
		 bool bResult=GetWorld()->SweepSingleByChannel(
		 	HitResult,
		 	Character->GetActorLocation(),
		 	Character->GetActorLocation()+Character->GetActorForwardVector()*200.0f,
		 	FQuat::Identity,
		 	ECC_GameTraceChannel1,
		 	FCollisionShape::MakeSphere(50.0f),
		 	Params
		 );
	}
}

void UAttackComponent::DisalbeCollsion()
{
	if(mAttackCollision)
	{
		mAttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void UAttackComponent::TakeDamage()
{
	//FDamageEvent DamageEvent;
}

void UAttackComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherComp)
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green,TEXT("TakeDamage"));

}





