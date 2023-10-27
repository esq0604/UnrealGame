// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CustomSpringArmComponent.h"

#include "Component/TargetingComponent.h"
#include "Components/SlateWrapperTypes.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UCustomSpringArmComponent::UCustomSpringArmComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	bUsePawnControlRotation = true; // Rotate the arm based on the controller
	bEnableCameraLag = true;
	bEnableCameraRotationLag = false;
	CameraLagSpeed = 3.f;
	CameraRotationLagSpeed = 2.f;
	CameraLagMaxDistance = 100.f;
}

// Called every frame
void UCustomSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsCameraLockedToTarget())
	{
		DrawDebugSphere(GetWorld(), CameraTarget->GetComponentLocation(), 20.f, 16, FColor::Red); //Draw target point
		UWidgetComponent* TargetWidget =Cast<UWidgetComponent>(CameraTarget->GetOwner()->GetComponentByClass(UWidgetComponent::StaticClass()));
		TargetWidget->SetVisibility(true);
		// Break lock if player is too far from target
		if ((CameraTarget->GetComponentLocation() - GetComponentLocation()).Size() > MaxTargetLockDistance)
		{
			if (bUseSoftLock)
			{
				// Try switch to a new target in range
				if (UTargetingComponent* NewCameraTarget = GetLockTarget())
				{
					LockToTarget(NewCameraTarget);
				}
				else
				{
					BreakTargetLock();
				}
			}
			else
			{
				BreakTargetLock();
			}
		}
	}
	else
	{
		if (bUseSoftLock) // Attempt to auto target nearby enemy
		{
			if (UTargetingComponent* NewCameraTarget = GetLockTarget())
			{
				if (!bSoftlockRequiresReset) // Soft-lock is reset?
				{
					LockToTarget(NewCameraTarget);
				}
			}
			else // If player forcibly broke soft-lock, reset it when no target is within range
			{
				bSoftlockRequiresReset = false;
			}
		}
	}

	// Draw debug
	if (bDrawDebug)
	{
		for (UTargetingComponent* Target : GetTargetComponents())
		{
			DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), Target->GetComponentLocation(), FColor::Green);
		}

		// Draw target inclusion sphere
		DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), MaxTargetLockDistance, 32, FColor::Cyan);

		UKismetSystemLibrary::DrawDebugString(this, FVector::ZeroVector,
		                                      bUseSoftLock ? "Soft-lock Enabled" : "Soft-lock Disabled", GetOwner(),
		                                      FLinearColor::Green);

		if (bSoftlockRequiresReset)
		{
			UKismetSystemLibrary::DrawDebugString(this, FVector(0.f, 0.f, -10.f), "Soft-lock Requires Reset",
			                                      GetOwner(), FLinearColor::Green);
		}
	}
}

void UCustomSpringArmComponent::ToggleCameraLock()
{
	if (bUseSoftLock) // Soft-lock supersedes player input
	{
		bSoftlockRequiresReset = false;
		return;
	}

	// If CameraTarget is set, unset it
	if (IsCameraLockedToTarget())
	{
		BreakTargetLock();
		return;
	}

	UTargetingComponent* NewCameraTarget = GetLockTarget();

	if (NewCameraTarget != nullptr)
	{
		LockToTarget(NewCameraTarget);
	}
}

void UCustomSpringArmComponent::ToggleSoftLock()
{
	bUseSoftLock = !bUseSoftLock;

	if (bUseSoftLock)
	{
		bSoftlockRequiresReset = false;
	}
	else
	{
		BreakTargetLock();
	}
}

void UCustomSpringArmComponent::LockToTarget(UTargetingComponent* NewTargetComponent)
{
	CameraTarget = NewTargetComponent;
	bEnableCameraRotationLag = true;
	//GetCharacterMovement()->bOrientRotationToMovement = false;
}

void UCustomSpringArmComponent::BreakTargetLock()
{
	if (IsCameraLockedToTarget())
	{
		UWidgetComponent* TargetWidget =Cast<UWidgetComponent>(CameraTarget->GetOwner()->GetComponentByClass(UWidgetComponent::StaticClass()));
		TargetWidget->SetVisibility(false);

		CameraTarget = nullptr;
		//GetController()->SetControlRotation(FollowCamera->GetForwardVector().Rotation());
		bEnableCameraRotationLag = false;
		//GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}

UTargetingComponent* UCustomSpringArmComponent::GetLockTarget()
{
	TArray<UTargetingComponent*> AvailableTargets = GetTargetComponents();
	if (AvailableTargets.Num() == 0)
	{
		return nullptr;
	}
	// Get the target with the smallest angle difference from the camera forward vector
	float ClosestDotToCenter = 0.f;
	UTargetingComponent* TargetComponent = nullptr;

	for (int32 i = 0; i < AvailableTargets.Num(); i++)
	{
		float Dot = FVector::DotProduct(GetForwardVector(), (AvailableTargets[i]->GetComponentLocation() - GetComponentLocation()).GetSafeNormal());
		if (Dot > ClosestDotToCenter)
		{
			ClosestDotToCenter = Dot;
			TargetComponent = AvailableTargets[i];
		}
	}
	return TargetComponent;
}

void UCustomSpringArmComponent::SwitchTarget(EDirection SwitchDirection)
{
	if (!IsCameraLockedToTarget()) return;

	TArray<UTargetingComponent*> AvailableTargets = GetTargetComponents();	// Get targets within lock-on range	
	if (AvailableTargets.Num() < 2) return;	// Must have an existing camera target and 1 additional target

	FVector CurrentTargetDir = (CameraTarget->GetComponentLocation() - GetComponentLocation()).GetSafeNormal();

	TArray<UTargetingComponent*> ViableTargets;

	for (UTargetingComponent* Target : AvailableTargets)
	{
		//  Don't consider current target as a switch target
		if (Target == CameraTarget) continue;

		FVector TargetDir = (Target->GetComponentLocation() - GetComponentLocation()).GetSafeNormal();
		FVector Cross = FVector::CrossProduct(CurrentTargetDir, TargetDir);

		if ((SwitchDirection == EDirection::Left && Cross.Z < 0.f)	// Negative Z indicates left
			|| (SwitchDirection == EDirection::Right && Cross.Z > 0.f))	// Positive Z indicates righ
				{
			ViableTargets.AddUnique(Target);
				}
	}

	if (ViableTargets.Num() == 0) return;


	//	현재 타겟과 각도 차이가 가장 작은 타겟을 선택합니다.
	int32 BestDotIdx = 0;
	for (int32 i = 1; i < ViableTargets.Num(); i++)
	{
		float BestDot = FVector::DotProduct(CurrentTargetDir, (ViableTargets[BestDotIdx]->GetComponentLocation() - GetComponentLocation()).GetSafeNormal());
		float TestDot = FVector::DotProduct(CurrentTargetDir, (ViableTargets[i]->GetComponentLocation() - GetComponentLocation()).GetSafeNormal());

		// Higher dot product indicates this target vector has a smaller angle than the previous best
		if (TestDot > BestDot)
			BestDotIdx = i;
	}

	LockToTarget(ViableTargets[BestDotIdx]);
}

TArray<UTargetingComponent*> UCustomSpringArmComponent::GetTargetComponents()
{
	TArray<UPrimitiveComponent*> TargetPrims;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { EObjectTypeQuery::ObjectTypeQuery2 }; // World dynamic object type

	// Overlap check for targetable component
	UKismetSystemLibrary::SphereOverlapComponents(GetOwner(),GetComponentLocation(),MaxTargetLockDistance, ObjectTypes,UTargetingComponent::StaticClass(),TArray<AActor*>{GetOwner()},TargetPrims);

	TArray<UTargetingComponent*> TargetComps;
	for (UPrimitiveComponent* Comp : TargetPrims)
	{
		TargetComps.Add(Cast<UTargetingComponent>(Comp));
	}

	return TargetComps;
}

/* 카메라가 현재 타겟에 고정되어 있으면 참입니다. */
bool UCustomSpringArmComponent::IsCameraLockedToTarget()
{
	return CameraTarget != nullptr;
}

