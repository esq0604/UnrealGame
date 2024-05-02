// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/DeveloperSettings.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameSetting.generated.h"

class UDataTable;

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Save Game Settings")) // 'defaultconfig' = "Save object config only to Default INIs, never to local INIs."
class RETARGETINGTEST_API USaveGameSetting : public USaveGame
{
	GENERATED_BODY()
	
public:
	USaveGameSetting();

	UPROPERTY(VisibleAnywhere, Category="Basic")
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category="Basic")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category="Basic")
	uint32 UserIndex;
	
};
