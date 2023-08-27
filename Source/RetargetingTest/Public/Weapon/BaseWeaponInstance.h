// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "BaseWeaponInstance.generated.h"

class UGameplayAbility_MeleeWeapon;
struct FGameplayAbilitySpecHandle;
class UGameplayAbility;
class ACharacterBase;
class UWeaponCollisionComponent;
struct FGameplayEventData;
struct FGameplayAbilitySpec;
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

	
	void OnEquipped();

	//	Getter
	FName GetWeaponTraceStartSocketName() const;
	FName GetWeaponTraceEndSocketName() const; 
	TWeakObjectPtr<UWeaponCollisionComponent> GetCollisionComponent() const;
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
	UStaticMeshComponent* GetWeaponStateMeshComponent() const {return WeaponStaticMeshComponent;}

private:
	void OnHitDelegateFunction(FGameplayEventData EventData,const FHitResult HitResult);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Weapon|")
	ACharacterBase* OwningCharacter;

	// Ability 
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Weapon|Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Weapon|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	// WeaponInfo for CollisionComponent 
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Weapon|Socket")
	FName WeaponTraceStartSocketName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Weapon|Socket")
	FName WeaponTraceEndSocketName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Weapon|Socket")
	FName AttachSocketName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=ture))
	UStaticMeshComponent* WeaponStaticMeshComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UStaticMesh* WeaponStaticMesh;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Weapon|Component")
	TObjectPtr<UWeaponCollisionComponent> CollisionComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Weapon|Abilities")
	FGameplayTagContainer AttackAbilityTagContainer;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Weapon|Abilities")
	TArray<TObjectPtr<UGameplayAbility>> AbilityInstances;


};
