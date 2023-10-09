// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "EquipmentItem.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Interface/Interactable.h"
#include "Interface/Useable.h"
#include "BaseWeaponInstance.generated.h"

class UGameplayAbility_MeleeWeapon;
struct FGameplayAbilitySpecHandle;
class UCustomGameplayAbility;
class ACharacterBase;
class UWeaponCollisionComponent;
struct FGameplayEventData;
struct FGameplayAbilitySpec;


UCLASS()
class RETARGETINGTEST_API ABaseWeaponInstance : public AEquipmentItem, public IAbilitySystemInterface, public IInteractable,public IUseable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeaponInstance();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
 
	virtual void AddAbilities();

	virtual void RemoveAbilities();


	//Equip, UnEquipped
	UFUNCTION(BlueprintImplementableEvent)
	void OffDetecte();
	void OnEquipped(ACharacter* Character);
	void OffEquipped(ACharacter* Character);
	
	//	Getter
	FName GetWeaponTraceStartSocketName() const;
	FName GetWeaponTraceEndSocketName() const; 
	UWeaponCollisionComponent* GetCollisionComponent() const;

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
	virtual void Interact_Implementation() override;
	virtual void UseItem_Implementation(ACharacterBase* Character) override;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Weapon|")
	ACharacterBase* OwningCharacter;

	// Ability 
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Weapon|Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="Weapon|Abilities")
	TArray<TSubclassOf<UCustomGameplayAbility>> Abilities;
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
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Weapon|Component")
	TObjectPtr<UWeaponCollisionComponent> WeaponCollisionComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Weapon|Abilities")
	FGameplayTagContainer AttackAbilityTagContainer;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Weapon|Abilities")
	TArray<TObjectPtr<UCustomGameplayAbility>> AbilityInstances;
	bool bIsEquipped=false;

private:
};
