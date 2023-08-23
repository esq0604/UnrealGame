// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/TargetingComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Interface/Targeting.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
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

void UTargetingComponent::SetTargetActor(AActor* NewTargetActor)
{
	TargetActor=NewTargetActor;
}

void UTargetingComponent::SetIstargeting(bool EnabledTargeting)
{
	bIsTargeting=EnabledTargeting;
}


AActor* UTargetingComponent::FindTarget()
{
	AActor* FoundTarget=nullptr;
	
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
		FoundTarget = OutHitResult.GetActor();
		if(FoundTarget->GetClass()->ImplementsInterface(UTargeting::StaticClass()))
		{
			return FoundTarget;
		}
	}
	return FoundTarget;
}

void UTargetingComponent::EnableLockOn()
{
	SetTargetActor(FindTarget());
	if(TargetActor)
	{
		SetIstargeting(true);
	}
}

void UTargetingComponent::DisableLockOn()
{
	SetIstargeting(false);
	SetTargetActor(nullptr);
}

void UTargetingComponent::ToggleLockOn()
{
	if(bIsTargeting)
	{
		DisableLockOn();
		return;
	}
	
	EnableLockOn();
	return;
	
}

bool UTargetingComponent::TargetCanBeTargeted()
{
	//Dead상태가 아니라면, 현재 Disable 상태가 아니라면 타게팅이 가능해야합니다. 
	//TODO : 1. 게임플레이태그를 가져와서 로직을 작성한다. 2. 캐스팅을 통해 bool값을 가져온다.
	return true;
}

// Called every frame
void UTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bIsTargeting)
	{
		UpdateTargetControlRotation();
	}
	
}

void UTargetingComponent::UpdateTargetControlRotation()
{
	if(OwnerController.IsValid() && TargetActor)
	{
		if(TargetCanBeTargeted())
		{
			const FVector OwnerLocation = GetOwner()->GetActorLocation();
			const FVector TargetLocation = TargetActor->GetActorLocation();
			const FRotator OwnerControlRotation = OwnerController->K2_GetActorRotation(); 
			
			const FVector ApplyZOffsetTargetLocation=TargetLocation - FVector(0,0,zOffSet);
			const FRotator FindLootAtRotator = UKismetMathLibrary::FindLookAtRotation(OwnerLocation,ApplyZOffsetTargetLocation);

			const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
			const FRotator RInterpRot = UKismetMathLibrary::RInterpTo(OwnerControlRotation,FindLootAtRotator,DeltaTime,TargetRotationInterSpeed);

			const FRotator NewRot =FRotator(OwnerControlRotation.Roll,RInterpRot.Pitch,RInterpRot.Yaw);
			OwnerController->SetControlRotation(NewRot);
		}
		else
		{
			DisableLockOn();
		}
	}
}

