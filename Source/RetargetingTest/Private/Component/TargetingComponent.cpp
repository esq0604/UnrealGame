// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/TargetingComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Interface/Targeting.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UTargetingComponent::UTargetingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTargetingComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter=Cast<ACharacter>(GetOwner());
	OwnerController=OwnerCharacter->GetController();
	FollowCamera=Cast<UCameraComponent>(OwnerCharacter->GetComponentByClass(UCameraComponent::StaticClass()));
	
}

AActor* UTargetingComponent::FindTarget()
{
	UE_LOG(LogTemp,Warning,TEXT("FindTarget"));
	FHitResult OutHitResult;
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(GetOwner());
	
	bool bHit = UKismetSystemLibrary::SphereTraceSingle(
	GetWorld(),
	GetOwner()->GetActorLocation(),
	(FollowCamera->GetForwardVector()*TargetingDistance) + (GetOwner()->GetActorLocation()),
	TargetingRadius,
	UEngineTypes::ConvertToTraceType(ECC_Pawn),
	false,
	IgnoreActors,
	EDrawDebugTrace::ForDuration,
	OutHitResult,
	true,
	FLinearColor::Red,
	FLinearColor::Green,
	5.0f
	);

	if(bHit)
	{
		AActor* HitActor = OutHitResult.GetActor();
		if(HitActor->GetClass()->ImplementsInterface(UTargeting::StaticClass()))
		{
			return HitActor;
		}
	}
	return nullptr;
}


// Called every frame
void UTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTargetingComponent::RotateToTarget()
{

}

