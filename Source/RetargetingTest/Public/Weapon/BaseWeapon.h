// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class ACharacter;
UCLASS()
class RETARGETINGTEST_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
public:
	
	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetWeaponMesh() const {return WeaponMesh;}

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetWeaponStateMeshComponent() const {return WeaponMeshCompnent;}
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=ture))
	UStaticMeshComponent* WeaponMeshCompnent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UStaticMesh* WeaponMesh; 
private:


};
