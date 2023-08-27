// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/WeaponCollisionComponent.h"

#include "Abilities/GameplayAbilityTypes.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SceneComponent.h"


// Sets default values for this component's properties
UWeaponCollisionComponent::UWeaponCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UWeaponCollisionComponent::BeginPlay()
{
	Super::BeginPlay();
	//커스텀 오브젝트 타입을 가져와서 추가해주기. 
	//TraceObjectType.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel3));
	// ...
}

/**
 * 콜리전에 닿은 오브젝트에 대한 데이터를 생성하여, 바인딩된 WeaponInstance에 보내줍니다.
 */
void UWeaponCollisionComponent::CollisionEnable()
{
	TArray<FHitResult> HitResults;

	const FVector WeaponStartLoc =  CollisionMeshComponent->GetSocketLocation(WeaponStartName);
	const FVector WeaponEndLoc = CollisionMeshComponent->GetSocketLocation(WeaponEndName);
	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),WeaponStartLoc,WeaponEndLoc,TraceRadius,TraceObjectType,false,TraceActorToIgnore,EDrawDebugTrace::ForDuration,HitResults,true,FColor::Red,FColor::Green,DebugTime);
	
	for(FHitResult hitResult : HitResults)
	{
		if(CanHitActor(hitResult.GetActor()))
		{
			FGameplayEventData Data;
			Data.Instigator=GetOwner();
			Data.Target=hitResult.GetActor();
			OnHitDelegate.Execute(Data,hitResult);
		}
	}
}


// Called every frame
void UWeaponCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(mCollisionEnable)
	{
		CollisionEnable();
	}
}

void UWeaponCollisionComponent::SetWeaponStart(FName WeaponStart)
{
	WeaponStartName=WeaponStart;
}

void UWeaponCollisionComponent::SetWeaponEnd(FName WeaponEnd)
{
	WeaponEndName=WeaponEnd;
}

void UWeaponCollisionComponent::SetCollisionEnable(bool CollisionEnable)
{
	mCollisionEnable=CollisionEnable;

	if(!CollisionEnable)
	{
		AlreadyHitActor.Empty();
	}
}

void UWeaponCollisionComponent::SetCollisionMeshComp(UPrimitiveComponent* CollisionMesh)
{
	CollisionMeshComponent=CollisionMesh;
}

/**
 *  한 동작에서 트레이스를 발생시킬때, 이미 트레이스에 닿은액터를 또 닿았는지 체크하지 위한 검사함수입니다.
 */
bool UWeaponCollisionComponent::CanHitActor(AActor* CheckActor)
{
	if(AlreadyHitActor.Contains(CheckActor))
	{
		return false;
	}
	
	AlreadyHitActor.AddUnique(CheckActor);
	return true;
}