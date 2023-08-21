// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UObject/Object.h"
#include "EnemyAIController.generated.h"

class UAISenseConfig_Damage;
class ABaseMonster;
class UAISenseConfig_Sight;
struct FAIStimulus;
/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	AEnemyAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	
	void SetPerceptionSystem();
	UFUNCTION()
	void OnPerceptionUpdate(AActor* UpdatedActor,const FAIStimulus Simulus);

protected:
	TWeakObjectPtr<ABaseMonster> BaseEnemy;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="AIController | Component")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionCompnent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="AIController")
	TWeakObjectPtr<AActor> TargetActor;

	UPROPERTY(EditInstanceOnly,BlueprintReadWrite,Category="AIController | Perception Config")
	TWeakObjectPtr<UAISenseConfig_Sight> SightConfig;

	UPROPERTY(EditInstanceOnly,BlueprintReadWrite,Category="AIController | Perception Config")
	TWeakObjectPtr<UAISenseConfig_Damage> DamageConfig;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AIController | AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BehaviorTree;
public:

	//SightConfig Properties Init 
	const float AISightRadius=3000.0f;
	const float AILoseSightRadius=3500.0f;
	const float AIVisionAngleDegrees=45.0f;
	const float AIAutoSuccessRangeFromLastSeenLocation=2500.0f;
};
