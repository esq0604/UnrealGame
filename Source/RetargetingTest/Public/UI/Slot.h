// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Slot.generated.h"

class APlayerBase;
class ACharacterBase;
class UTextBlock;
class UImage;

/**
 * 술롯의타입을 나타냅니다. 슬롯은 각각 인벤토리, 퀵슬롯, 장비에 쓰이기 때문에.
 * 슬롯의 타입 또한 장비아이템, 소비아이템, 퀵슬롯에서 사용할아이템, 퀵슬롯에서 사용할 스킬로 나눴습니다.
 */
UENUM()
enum class ESlotType : uint8
{
	SLOT_INVENTORY,
	SLOT_QUICK,
	SLOT_EQUIP
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
	void SetCharacter(APlayerBase* NewCharacter);
	void SetIndex(int32 NewIndex);
	void SetImg(UTexture2D* NewImg);
	void Action();
	ESlotType GetSlotType() const;
	int32 GetIndex() const;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
public:
	//드래그시 보일 SlotClass 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USlot> DragVisualClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Count; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UImage* Img;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* CountText;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 SlotNum;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 Index;


protected:
	APlayerBase* Player;
private:
	ESlotType SlotType;

};

