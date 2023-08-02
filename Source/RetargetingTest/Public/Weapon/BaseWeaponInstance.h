// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "BaseWeaponInstance.generated.h"

struct FGameplayAbilitySpecHandle;
class UGameplayAbility;
class ACharacterBase;
UCLASS()
class RETARGETINGTEST_API ABaseWeaponInstance : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeaponInstance();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
 
	virtual void AddAbilities();

	virtual void RemoveAbilities();

	void SetOwningCharacter(ACharacterBase* InOwningCharacter);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Tag")
	FGameplayTag WeaponTag;
	
	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetWeaponMesh() const {return WeaponMesh;}

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetWeaponStateMeshComponent() const {return WeaponMeshCompnent;}
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=ture))
	UStaticMeshComponent* WeaponMeshCompnent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UStaticMesh* WeaponMesh;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon|")
	ACharacterBase* OwningCharacter;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Weapon|Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Weapon|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
private:


};
