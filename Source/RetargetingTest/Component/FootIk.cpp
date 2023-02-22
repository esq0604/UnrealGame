// Fill out your copyright notice in the Description page of Project Settings.


#include "FootIk.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RetargetingTest/Player/RetargetingTestCharacter.h"

// Sets default values for this component's properties
UFootIk::UFootIk()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called when the game starts
void UFootIk::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Character=Cast<ARetargetingTestCharacter>(GetOwner());
	//IKCapsuleHalfHeight=Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	//UE_LOG(LogTemp,Warning,TEXT("%d"),IKCapsuleHalfHeight);
}

void UFootIk::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void UFootIk::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	Trace_Left=IK_FootTrace(55.0f,"foot_l");
	Trace_Right=IK_FootTrace(55.0f,"foot_r");
	IK_UpdateFootRotation(DeltaTime,NormalToRotator(Trace_Left.ImpactLocation),&FootRotation_Left,13.0f);
	IK_UpdateFootRotation(DeltaTime,NormalToRotator(Trace_Right.ImpactLocation),&FootRotation_Right,13.0f);

	float fHipsOffset = UKismetMathLibrary::Min(Trace_Left.Offset, Trace_Right.Offset);
	if (fHipsOffset < 0.0f == false) fHipsOffset = 0.0f;
	IK_Update_FootOffset(DeltaTime, fHipsOffset, &m_fHipOffset, 13.0f);
	IK_Update_CapsuleHalfHeight(DeltaTime, fHipsOffset, false);

	IK_Update_FootOffset(DeltaTime,Trace_Left.Offset-fHipsOffset, &FootOffset_Left, 13.0f);
	IK_Update_FootOffset(DeltaTime,-1*(Trace_Right.Offset-fHipsOffset), &FootOffset_Right, 13.0f);

}

FST_IK_TraceInfo UFootIk::IK_FootTrace(float TraceDistance, FName Socket)
{
	FST_IK_TraceInfo TraceInfo;
	
	FVector SocketLocation = Character->GetMesh()->GetSocketLocation(Socket);
	FVector LineStart = FVector(SocketLocation.X,SocketLocation.Y,Character->GetActorLocation().Z);
	FVector LineEnd = FVector(SocketLocation.X,SocketLocation.Y,(Character->GetActorLocation().Z -IKCapsuleHalfHeight)-TraceDistance);

	FHitResult HitResult;
	TArray<AActor*> Ignore;
	Ignore.Add(GetOwner());

	bool IsDebug = true;
	EDrawDebugTrace::Type Debug = EDrawDebugTrace::None;
	
	if(IsDebug == true)  Debug= EDrawDebugTrace::ForOneFrame;

	bool IsResult = UKismetSystemLibrary::LineTraceSingle(GetWorld(),LineStart,LineEnd,UEngineTypes::ConvertToTraceType(ECC_Visibility),true,Ignore,Debug,HitResult,true);

	TraceInfo.ImpactLocation=HitResult.ImpactNormal;
	if(HitResult.IsValidBlockingHit()==true)
	{
		float ImpactLength =(HitResult.ImpactPoint-HitResult.TraceEnd).Size();
		TraceInfo.Offset = 5.0f+(ImpactLength-TraceDistance);
		UE_LOG(LogTemp,Warning,TEXT("%d  %d "),ImpactLength, TraceDistance);

	}
	else
	{
		TraceInfo.Offset=0.0f;
	}
	return TraceInfo;
	
}

FRotator UFootIk::NormalToRotator(FVector Vector)
{
	float Atan2_1 = UKismetMathLibrary::DegAtan2(Vector.Y,Vector.Z);
	float Atan2_2 = UKismetMathLibrary::DegAtan2(Vector.X,Vector.Z);
	Atan2_2*=-1.0f;
	return FRotator(Atan2_2,0.0f,Atan2_1);
	
}

void UFootIk::IK_UpdateFootRotation(float DeltaTime, FRotator TargetVal, FRotator* FootRotatorVal, float InterpSpeed)
{
	FRotator InterpRotator = UKismetMathLibrary::RInterpTo(*FootRotatorVal,TargetVal,DeltaTime,InterpSpeed);
	*FootRotatorVal = InterpRotator;
}

//발 높이에 따라 캡슐콜라이더의 위치를 조절합니다.
void UFootIk::IK_Update_CapsuleHalfHeight(float fDeltaTime, float fHipsShifts, bool bResetDefault)
{
	UCapsuleComponent* pCapsule = Character->GetCapsuleComponent();
	if (pCapsule == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("IK : Capsule is NULL"));
		return;
	}
 
	//! Get Half Height of capsule component
	float fCapsuleHalf = 0.0f;
	if (bResetDefault == true)
	{
		fCapsuleHalf = IKCapsuleHalfHeight;
	}
	else
	{
		float fHalfAbsSize = UKismetMathLibrary::Abs(fHipsShifts) * 0.5f;
		fCapsuleHalf = IKCapsuleHalfHeight - fHalfAbsSize;
	}
 
	//! Set capsule component height with FInterpTo 
	float fScaledCapsuleHalfHeight = pCapsule->GetScaledCapsuleHalfHeight();
	float fInterpValue = UKismetMathLibrary::FInterpTo(fScaledCapsuleHalfHeight, fCapsuleHalf, fDeltaTime, 13.0f);
 
	pCapsule->SetCapsuleHalfHeight(fInterpValue, true);
}

void UFootIk::IK_Update_FootOffset(float fDeltaTime, float fTargetValue, float* fEffectorValue, float fInterpSpeed)
{
	float fInterpValue = UKismetMathLibrary::FInterpTo(*fEffectorValue, fTargetValue, fDeltaTime, fInterpSpeed);
	*fEffectorValue = fInterpValue;
}