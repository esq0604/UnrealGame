// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/Interactable.h"

// Sets default values
AInteractable::AInteractable()
{
	InteractableHelpText=FString("Press E to interat with item.");
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}


void AInteractable::Interact_Implementation()
{
	GLog->Log("Interact base class : Interact() YOU SHOULD NOT BE SEEING THIS");
	//character -> getinventory() =this;
	
}


