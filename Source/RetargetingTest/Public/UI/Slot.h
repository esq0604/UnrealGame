// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Slot.generated.h"

enum class EItemType : uint8;
class UInventoryUI;
class UInventoryComponent;
class ACharacterBase;
class UTextBlock;
class UImage;

/**
 * 술롯의타입을 나타냅니다. 슬롯은 각각 인벤토리, 퀵슬롯, 장비에 쓰이기 때문에.
 * TODO : 슬롯에서 인벤토리 UI를 들고있지 않기위해서는 NativeOnMouseEvent를 InventoryUI에서 WidgetSize에 맞춰서 계산하여야합니다. 
 *
 */
UENUM()
enum class ESlotType : uint8
{
	SLOT_INVENTORY,
	SLOT_QUICK,
	SLOT_EQUIP,
};
UCLASS()
class RETARGETINGTEST_API USlot : public UUserWidget
{
	GENERATED_BODY()
public:
	void Refresh();
	
	UFUNCTION(BlueprintCallable)
	void Init();

	void SetType(ESlotType NewSlotType);
	void SetIndex(int32 NewIndex);
	void SetImg(UTexture2D* NewImg);
	void SetAmountText(int32 Amount);
	void SetItemType(EItemType Type);
	void SetInventoryUI(UInventoryUI* NewInventoryUI);
	void SetSlotType(ESlotType Type);
	
	ESlotType GetSlotType() const;
	int32 GetIndex() const;
	void Action();
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

private:
	void ShowAmountText();
	void HideAmountText();
public:
	//드래그시 보일 SlotClass 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USlot> DragVisualClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Count; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UImage* Img;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* DefaultTexture;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* AmountText;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 SlotNum;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 Index;

protected:
private:
	ESlotType SlotType;
	EItemType ItemType;
	UPROPERTY()
	UInventoryUI* InventoryUI;


};

