#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct RETARGETINGTEST_API GameTags : public FGameplayTagNativeAdder
{
public:
	FORCEINLINE static const GameTags& Get() {return MyGameTags;}

public:
	virtual void AddTags() override;

	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:
	static GameTags MyGameTags;

public:
	FGameplayTag State_Walk;
	FGameplayTag State_Idle;
	FGameplayTag State_Dodge;
	FGameplayTag State_Jump;
	FGameplayTag State_Attack;
	FGameplayTag State_Sprint;
};
