// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "EquipmentItem.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "Data/WeaponDataAsset.h"
#include "GameFramework/Actor.h"
#include "Interface/Interactable.h"
#include "Interface/Useable.h"
#include "BaseWeaponItem.generated.h"

class UWeaponDataAsset;
class UGameplayAbility_MeleeWeapon;
struct FGameplayAbilitySpecHandle;
class UCustomGameplayAbility;
class ACharacterBase;
class UWeaponCollisionComponent;
struct FGameplayEventData;
struct FGameplayAbilitySpec;


UCLASS(Abstract)
class RETARGETINGTEST_API ABaseWeaponItem   : public AEquipmentItem, public IAbilitySystemInterface,public IUseable
{
	GENERATED_BODY()

	//Public Function
public:
	// Sets default values for this actor's properties
	ABaseWeaponItem();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void RemoveAbilities();


	//Equip, UnEquipped
	UFUNCTION(BlueprintImplementableEvent)
	void OffDetecte();
	virtual void Equip(ACharacter* Character,UItemDataAsset* InItemData) override final;
	virtual void UnEquip(ACharacter* Character) override final;
	
	//	Getter
	FORCEINLINE FName GetWeaponTraceStartSocketName() const {return WeaponData->WeaponSocketName.TraceStartSocketName;}
	FORCEINLINE FName GetWeaponTraceEndSocketName() const {	return WeaponData->WeaponSocketName.TraceEndSocketName;} 
	FORCEINLINE UWeaponCollisionComponent* GetCollisionComponent() const {return WeaponCollisionComp; }
	FORCEINLINE UStaticMesh* GetWeaponMesh() const {return StaticMeshComponent->GetStaticMesh();}
	FORCEINLINE const UWeaponDataAsset* GetWeaponData() const { return WeaponData;}

	//Protected Function
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;


	//Privte Function
private:
	void OnHitDelegateFunction(FGameplayEventData EventData,const FHitResult HitResult);

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Tag")
	FGameplayTag WeaponTag;
	

private:
	//virtual void Interact_Implementation() override;
protected:

private:

	// Ability 
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Weapon|Component")
	TObjectPtr<UWeaponCollisionComponent> WeaponCollisionComp;

	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess=true))
	UWeaponDataAsset* WeaponData;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Weapon|Abilities")
	FGameplayTag AttackAbilityTag;
	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess=true),Category="Weapon|Abilities")
	TArray<TObjectPtr<UCustomGameplayAbility>> AbilityInstances;
	bool bIsEquipped=false;
};
