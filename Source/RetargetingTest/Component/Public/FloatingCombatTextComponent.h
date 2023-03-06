// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatingCombatTextComponent.generated.h"

class AFloatingDamageActor;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UFloatingCombatTextComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFloatingCombatTextComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void AddFloatingActor(const FText& Text, FVector WorldLocation);
private:
	//callback for when floating actor destroyed
	UFUNCTION(BlueprintCallable)
	void OnTextDestroyed(AActor* DestroyedActor);
	
	
private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="UFloatingCombatTextComponent",meta=(AllowPrivateAccess=true))
	TSubclassOf<AFloatingDamageActor> FloatingDamageActorClass =nullptr;

	//amount of vertical space between each damage number;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="UFloatingCombatTextComponent",meta=(AllowPrivateAccess=true))
	float TextVerticalSpacing =40.0f;

	//The amount of vertical offset to apply when spawning a new text actor
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="UFloatingCombatTextComponent",meta=(AllowPrivateAccess=true))  
	float TextVerticalOffset =100.0f; 

	//An array of all active floating text actors;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	TArray<AFloatingDamageActor*> ActiveFloatingDamageActors;

};
