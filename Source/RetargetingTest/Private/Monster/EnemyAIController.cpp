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
	//SetPerceptionSystem();
	BTComp=CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComp"));
	BBComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp,Warning,TEXT("OnPossess"));
	
	OwnerEnemy=Cast<ABaseMonster>(InPawn);
	BehaviorTree = OwnerEnemy->GetBehaviorTree();
	UBlackboardComponent* BlackboardComponent = Blackboard.Get();
	UseBlackboard(BehaviorTree->GetBlackboardAsset(),BlackboardComponent);
	RunBehaviorTree(BehaviorTree);
	this->Blackboard=BlackboardComponent;

}

void AEnemyAIController::BeginPlay()
{
	//RunBehaviorTree(BehaviorTree);

}

void AEnemyAIController::OnPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
		
	if(Blackboard)
	{
		Blackboard->SetValueAsObject(FName("TargetActor"),Actor);
		TargetActor=Actor;
	}
}

void AEnemyAIController::SetPerceptionSystem()
{
	SightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
	DamageConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Damage>("Damage Config");
	AIPerceptionComponent=CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);

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


