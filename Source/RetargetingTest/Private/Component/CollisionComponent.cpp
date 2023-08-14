// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CollisionComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SceneComponent.h"


// Sets default values for this component's properties
UCollisionComponent::UCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UCollisionComponent::BeginPlay()
{
	Super::BeginPlay();
	//커스텀 오브젝트 타입을 가져와서 추가해주기. 
	mTraceObjectType.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel3));
	// ...
}

void UCollisionComponent::CollisionEnable()
{
	TArray<FHitResult> HitResults;

	const FVector WeaponStartLoc =  mCollisionMeshComponent->GetSocketLocation(mWeaponStartName);
	const FVector WeaponEndLoc = mCollisionMeshComponent->GetSocketLocation(mWeaponEndName);
	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),WeaponStartLoc,WeaponEndLoc,mTraceRadius,mTraceObjectType,false,mTraceActorToIgnore,EDrawDebugTrace::ForDuration,HitResults,true,FColor::Red,FColor::Green,mDebugTime);
	
	for(FHitResult hitResult : HitResults)
	{
		if(CanHitActor(hitResult.GetActor()))
		{
			UE_LOG(LogTemp,Warning,TEXT("%s"),*hitResult.GetActor()->GetName());
			OnHitDelegate.Execute(hitResult);
		}
	}
}


// Called every frame
void UCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(mCollisionEnable)
	{
		CollisionEnable();
	}
}

void UCollisionComponent::SetWeaponStart(FName WeaponStart)
{
	mWeaponStartName=WeaponStart;
}

void UCollisionComponent::SetWeaponEnd(FName WeaponEnd)
{
	mWeaponEndName=WeaponEnd;
}

void UCollisionComponent::SetCollisionEnable(bool CollisionEnable)
{
	mCollisionEnable=CollisionEnable;

	if(!CollisionEnable)
	{
		AlreadyHitActor.Empty();
	}
}

void UCollisionComponent::SetCollisionMeshComp(UPrimitiveComponent* CollisionMesh)
{
	mCollisionMeshComponent=CollisionMesh;
}

/**
 *  한 동작에서 트레이스를 발생시킬때, 이미 트레이스에 닿은액터를 또 닿았는지 체크하지 위한 검사함수입니다.
 */
bool UCollisionComponent::CanHitActor(AActor* CheckActor)
{
	if(AlreadyHitActor.Contains(CheckActor))
	{
		return false;
	}
	
	AlreadyHitActor.AddUnique(CheckActor);
	return true;
}