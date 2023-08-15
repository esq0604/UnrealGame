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
class UCollisionComponent;
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
	
	void OnEquipped();
	
	FName GetWeaponTraceStartSocketName();
	FName GetWeaponTraceEndSocketName();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Tag")
	FGameplayTag WeaponTag;
	
	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetWeaponMesh() const {return WeaponStaticMesh;}

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetWeaponStateMeshComponent() const {return WeaponStaticMeshCompnent;}
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=ture))
	UStaticMeshComponent* WeaponStaticMeshCompnent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UStaticMesh* WeaponStaticMesh;
	
	UPROPERTY(BlueprintReadOnly, Category = "Weapon|")
	ACharacterBase* OwningCharacter;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Weapon|Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Weapon|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Weapon|Socket")
	FName WeaponTraceStartSocketName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Weapon|Socket")
	FName WeaponTraceEndSocketName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Weapon|Socket")
	FName AttachSocketName;

	// UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Weapon|Component")
	// TObjectPtr<UCollisionComponent> CollisionComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Weapon|Component")
	FGameplayTagContainer AttackAbilityTagContainer;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Weapon|Component")
	UGameplayAbility* AttackAbility;
private:
	void OnHitDelegateFunction(FHitResult HitResult);

};
