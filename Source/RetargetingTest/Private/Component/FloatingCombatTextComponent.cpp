// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Component/FloatingCombatTextComponent.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/UserInterfaceSettings.h"
#include "Kismet/GameplayStatics.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"
#include "RetargetingTest/Public/UI/FloatingDamageActor.h"

// Sets default values for this component's properties
UFloatingCombatTextComponent::UFloatingCombatTextComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UFloatingCombatTextComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ACharacterBase* Character = Cast<ACharacterBase>(GetOwner());

	
	
}


// Called every frame
void UFloatingCombatTextComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	const FVector2D ViewPortSize = UWidgetLayoutLibrary::GetViewportSize(this);

	//bad viewport size
	if(ViewPortSize.X<=0.0f || ViewPortSize.Y <=0.0f)
		return;

	//get the viewport scale(the dpi scale)
	const int32 viewportX = FGenericPlatformMath::FloorToInt(ViewPortSize.X);
	const int32 viewportY = FGenericPlatformMath::FloorToInt(ViewPortSize.Y);
	const float viewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(viewportX,viewportY));

	if(viewportScale <=0.0f)
		return;

	//소유 플레이어의 카메라 위치 가져오기
	const FVector cameraLocation=GetOwner<APawn>()->GetController<APlayerController>()->PlayerCameraManager->GetCameraLocation();

	//뷰포트 크기와 스케일에 따라 활성 텍스트 액터의 세로 위치를 조정하여 화면에 쌓여 보이도록 합니다.
	for(int32 i=1; i<ActiveFloatingDamageActors.Num(); ++i)
	{
		//플로팅 텍스트 액트로에서 우리(카메라)가 얼마나 멀리 떨어져 있는지에 따라 수직 오프셋을 계산합니다.
		AFloatingDamageActor* textActor = ActiveFloatingDamageActors[i];
		const float distance = FVector::Dist(cameraLocation, textActor->GetActorLocation());
		const float verticalOffset = distance/(ViewPortSize.X/viewportScale);

		//계산된 양만큼 플로팅 텍스트 액터의 위치를 조정합니다;
		textActor->SetActorLocation(textActor->GetActorLocation() + FVector(0.0f,0.0f,i*verticalOffset*TextVerticalSpacing));
	}
}

void UFloatingCombatTextComponent::AddFloatingActor(const FText& Text, FVector WorldLocation)
{
	if(FloatingDamageActorClass ==nullptr)
		return;

	//지정된 위치에 새 텍스트 액터를 스폰합니다.
	const FTransform spawnTransform = FTransform(FRotator::ZeroRotator, WorldLocation+ FVector(0.0f,0.0f,TextVerticalOffset));
	AFloatingDamageActor* newTextActor = GetWorld()->SpawnActorDeferred<AFloatingDamageActor>(FloatingDamageActorClass,spawnTransform,GetOwner());
	if(newTextActor==nullptr)
		return;

	//초기화 및 스폰
	newTextActor->Initialize(Text);
	newTextActor->OnDestroyed.AddDynamic(this,&UFloatingCombatTextComponent::OnTextDestroyed);
	UGameplayStatics::FinishSpawningActor(newTextActor,spawnTransform);

	//ActiveActor 액터 배열의 시작 부분에 새 텍스트 액터를 추가합니다.
	ActiveFloatingDamageActors.Insert(newTextActor,0);
}

void UFloatingCombatTextComponent::OnTextDestroyed(AActor* DestroyedActor)
{
	ActiveFloatingDamageActors.Pop();
}




