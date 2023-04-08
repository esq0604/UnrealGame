#include "GameTags.h"

#include "GameplayTagsManager.h"

GameTags GameTags::MyGameTags;

void GameTags::AddTags()
{
	AddTag(State_Walk,"State.Walk","");
	AddTag(State_Idle,"State.Idle","");
	AddTag(State_Dodge,"State.Dodge","");
	AddTag(State_Jump,"State.Jump","");
	AddTag(State_Attack,"State.Attack","");
	AddTag(State_Sprints,"State.Sprints","");

}

void GameTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}
