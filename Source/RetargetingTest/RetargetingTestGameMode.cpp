// Copyright Epic Games, Inc. All Rights Reserved.

#include "RetargetingTestGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Public/Player/CharacterBase.h"
#include "UObject/ConstructorHelpers.h"

void ARetargetingTestGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("GameMode BeginPlay"));
	ApplyHudChange();
}

ARetargetingTestGameMode::ARetargetingTestGameMode()
{
	// set default pawn class to our Blueprinted character
}

/**
 * 허드 상태를 확인한 다음, 그에 따라 applyHUD를 호출하여 원하는 허드를 적용합니다.
 */
void ARetargetingTestGameMode::ApplyHudChange()
{
	if(CurrentWidget !=nullptr)
	{
		CurrentWidget->RemoveFromParent();
	}

	switch (HUDState)
	{
	case EHUDState::HS_Ingame:
		{
			ApplyHUD(IngameHUDClass,false,false);
			break;
		}
	case EHUDState::HS_Inventory:
		{
			ApplyHUD(InventoryHUDClass,true,true);
			break;
		}
	case EHUDState::HS_Shop_General:
		{
			ApplyHUD(ShopGeneralHUDClass,true,true);
			break;
		}
	default:
		{
			ApplyHUD(IngameHUDClass,false,false);
			break;
		}
	}
}

/**
 * Getter function for hudstate
 */
uint8 ARetargetingTestGameMode::GetHUDState()
{
	return HUDState;
}

/**
 * Setter function for hudstate , applies the new state and then call applyHUDChange
 */
void ARetargetingTestGameMode::ChangeHUDState(uint8 NewState)
{
	HUDState=NewState;
	ApplyHudChange();
}

/**
 * Apples a hud to the screen , return true if successful, false otherwise
 * HUD는 열리면 마우스가 보여하고, 클릭이벤트를 설정해줘야함.
 * @param WidgetToApply - 변경할 위젯이 들어갑니다.
 * @param bShowMouseCursor - 마우스 커서의 가시성이 들어옵니다.
 * @param EnableClickEvent - 마우스의 클릭이벤트의 활성화 유무가 들어옵니다.
 */
bool ARetargetingTestGameMode::ApplyHUD(TSubclassOf<UUserWidget> WidgetToApply, bool bShowMouseCursor,
	bool EnableClickEvent)
{
	//플레이어와, 플레이어컨트롤러를 가져옵니다.
	ACharacterBase* MyCharacter = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(this,0));
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	//WidgetToApply가 nullptr이 아닌지 체크합니다.
	if(WidgetToApply!=nullptr)
	{
		//마우스 가시성 설정과 클릭 설정을 bShowMouseCursor,EnableClickEvent에 따라 설정합니다.
		MyController->bShowMouseCursor=bShowMouseCursor;
		MyController->bEnableClickEvents=EnableClickEvent;

		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(),WidgetToApply);

		if(CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;

	}
}
