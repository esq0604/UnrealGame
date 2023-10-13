// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
//무기에 대한 어빌리티 인풋아이디를 따로 나눠야할까.
//캐릭터 기본동작, 무기에대한 어빌리티를 따로 나눌지.
//오른손 어빌리티를 따로만들고, 무기의 해당 행동을 플레이어에게 초기화시 오른손어빌리티를 사용하도록하는방법으로 가볼것.
enum class EAbilityInputID : uint8
{
	None UMETA(DisplayName = "None" ),
	Confirm UMETA(DisplayName = "Confirm" ),
	Cancel UMETA(DisplayName = "Cancel" ),
	LeftClickAbility UMETA(DisplayName = "LeftClickAbility"),
	RightClickAbility UMETA(DisplayName = "RightClickAbility"),
	Sprint UMETA(DisplayName = "Sprint"),
	Jump UMETA(DisplayName = "Jump"),
	Interact UMETA(DisplayName = "Interact"),
	Dodge UMETA(DisplayNAme = "Dodge")
}; 