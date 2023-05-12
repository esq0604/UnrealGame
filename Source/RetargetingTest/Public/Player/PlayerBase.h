// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerBase.generated.h"

UCLASS()
class RETARGETINGTEST_API APlayerBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category="Inventory function")
	void UseItemAtInventorySlot(int32 Slot);

	UFUNCTION(BlueprintCallable, Category="Setter")
	bool AddItemToInventory(AItemBase* Item);

	/* Getter */
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	UFUNCTION(BlueprintCallable, Category="Player | Getter")
	TArray<AItemBase*> GetInventory() const;

	UFUNCTION(BlueprintCallable, Category="Player | Getter")
	AItemBase* GetItemAtInventory(int32 Index);

	UFUNCTION(BlueprintCallable, Category="Player | Getter")
	UTexture2D* GetThumnailAtInventorySlot(int32 Slot) const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
	AActor* CheckForInteractalbe();

	void ToggleInventory();

	UFUNCTION(BlueprintCallable)
	void Interact();
	
	void UseQuickSlot(int UsedSlotIdx);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HUD", meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> PlayerHUDClass;

	UPROPERTY(VisibleAnywhere, Category="HUD", meta=(AllowPrivateAccess=true))
	class UPlayerHUD* PlayerHUD;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TArray<class AItemBase*> Inventory;
	
private:
	class AItemBase* CurrentInteractable;
};


