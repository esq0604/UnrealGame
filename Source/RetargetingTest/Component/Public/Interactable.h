// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class RETARGETINGTEST_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintNativeEvent)
	void Interact();
	virtual void Interact_Implementation();

	//We can assume all interactables will have a static mesh
	UPROPERTY(EditAnywhere, Category="InteractableProperties")
	class UStaticMeshComponent* InteractableMesh;
	
	//We can assume all interactables will have some help text
	UPROPERTY(EditAnywhere, Category="InteractableProperties")
	FString InteractableHelpText;
};
