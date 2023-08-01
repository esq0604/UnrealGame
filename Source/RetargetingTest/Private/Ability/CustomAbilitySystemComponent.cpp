// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/CustomAbilitySystemComponent.h"

UCustomAbilitySystemComponent::UCustomAbilitySystemComponent()
{
}

FGameplayAbilitySpecHandle UCustomAbilitySystemComponent::FindAbilitySpecHandleForClass(
	TSubclassOf<UGameplayAbility> AbilityClass, UObject* OptionalSourceObject)
{
	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		
		TSubclassOf<UGameplayAbility> SpecAbilityClass = Spec.Ability->GetClass();
		if (SpecAbilityClass == AbilityClass)
		{
			if (!OptionalSourceObject || (OptionalSourceObject && Spec.SourceObject == OptionalSourceObject))
			{
				UE_LOG(LogTemp,Warning,TEXT("found spec"));
				return Spec.Handle;
			}
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("not found spec"))
	return FGameplayAbilitySpecHandle();
}
