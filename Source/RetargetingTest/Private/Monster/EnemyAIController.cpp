// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/BaseMonster.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Sight.h"

AEnemyAIController::AEnemyAIController()
{
	SetPerceptionSystem();
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	BaseEnemy=Cast<ABaseMonster>(InPawn);

	if(Blackboard)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->GetBlackboardAsset());
	}
}

void AEnemyAIController::BeginPlay()
{
	//AIPerceptionCompnent->OnPerceptionUpdated.AddDynamic(this,&AEnemyAIController::OnPerceptionUpdate);
	UE_LOG(LogTemp,Warning,TEXT("RunBehaviorTree"));
	RunBehaviorTree(BehaviorTree);
	
}

void AEnemyAIController::OnPerceptionUpdate(AActor* UpdatedActor,const FAIStimulus Simulus)
{
	if(Blackboard)
	{
		Blackboard->SetValueAsObject(FName("Target"),UpdatedActor);
	}
}

void AEnemyAIController::SetPerceptionSystem()
{
	SightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
	DamageConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Damage>("Damage Config");
	AIPerceptionCompnent=CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*AIPerceptionCompnent);

	SightConfig->SightRadius=AISightRadius;
	SightConfig->LoseSightRadius=AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees=AIVisionAngleDegrees;
	SightConfig->AutoSuccessRangeFromLastSeenLocation=AIAutoSuccessRangeFromLastSeenLocation;
	
	SightConfig->DetectionByAffiliation.bDetectEnemies=true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies=true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals=true;

	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->ConfigureSense(*DamageConfig);

	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this,&AEnemyAIController::OnPerceptionUpdate);
}


