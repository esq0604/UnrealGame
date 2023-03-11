// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RetargetingTestGameMode.generated.h"

UCLASS(minimalapi)
class ARetargetingTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
public:
	ARetargetingTestGameMode();

	enum EHUDState : uint8
	{
		HS_Ingame,
		HS_Inventory,
		HS_Shop_General,
		HS_Shop_Weapon,
	};

	void ApplyHudChange();
	
	uint8 GetHUDState();

	UFUNCTION(BlueprintCallable,Category="HUD function")
	void ChangeHUDState(uint8 NewState);

	bool ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply,bool bShowMouseCursor, bool EnableClickEvent);

protected:
	uint8 HUDState;
	
	 UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="HUDWidget")
	 TSubclassOf<class UUserWidget> IngameHUDClass;
	
	 UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="HUDWidget")
	 TSubclassOf<class UUserWidget> InventoryHUDClass;
	
	 UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="HUDWidget")
	 TSubclassOf<class UUserWidget> ShopGeneralHUDClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

};



