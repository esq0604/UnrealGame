// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingCombatTextComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/UserInterfaceSettings.h"
#include "RetargetingTest/Monster/BaseMonster.h"
#include "RetargetingTest/UI/FloatingDamageActor.h"
#include "Kismet/GameplayStatics.h"
#include "RetargetingTest/Player/RetargetingTestCharacter.h"

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
	ARetargetingTestCharacter* Character = Cast<ARetargetingTestCharacter>(GetOwner());

	
	
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

	//Get the owning player's camera location
	const FVector cameraLocation=GetOwner<APawn>()->GetController<APlayerController>()->PlayerCameraManager->GetCameraLocation();

	//Adjust the vertical location of the active text actors by the viewport size and scale that they apear evently stacked on the screen
	for(int32 i=1; i<ActiveFloatingDamageActors.Num(); ++i)
	{
		//Calculate the vertical offset based on how far we (the camera) are from the floating text actro
		AFloatingDamageActor* textActor = ActiveFloatingDamageActors[i];
		const float distance = FVector::Dist(cameraLocation, textActor->GetActorLocation());
		const float verticalOffset = distance/(ViewPortSize.X/viewportScale);

		//Adjust the floating text actor's location by the calcuated amount;
		textActor->SetActorLocation(textActor->GetActorLocation() + FVector(0.0f,0.0f,i*verticalOffset*TextVerticalSpacing));
	}
}

void UFloatingCombatTextComponent::AddFloatingActor(const FText& Text, FVector WorldLocation)
{
	if(FloatingDamageActorClass ==nullptr)
		return;

	//spawn new text actor at speified location
	const FTransform spawnTransform = FTransform(FRotator::ZeroRotator, WorldLocation+ FVector(0.0f,0.0f,TextVerticalOffset));
	AFloatingDamageActor* newTextActor = GetWorld()->SpawnActorDeferred<AFloatingDamageActor>(FloatingDamageActorClass,spawnTransform,GetOwner());
	if(newTextActor==nullptr)
		return;

	//Initlizer and finish sapwning the actor
	newTextActor->Initialize(Text);
	newTextActor->OnDestroyed.AddDynamic(this,&UFloatingCombatTextComponent::OnTextDestroyed);
	UGameplayStatics::FinishSpawningActor(newTextActor,spawnTransform);

	//Add the new text actor to the begning of the activeActor actor array 
	ActiveFloatingDamageActors.Insert(newTextActor,0);
}

void UFloatingCombatTextComponent::OnTextDestroyed(AActor* DestroyedActor)
{
	ActiveFloatingDamageActors.Pop();
}




