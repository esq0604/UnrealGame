// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Player/AbilitySystemTestCharacter.h"

#include "Ability/CharacterGameplayAbility.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RetargetingTest/Public/Ability/CharacterAbilitySystemComponent.h"
#include "RetargetingTest/Public/Attribute/CharacterAttributeSetBase.h"

// Sets default values
AAbilitySystemTestCharacter::AAbilitySystemTestCharacter(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Overlap);
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("State.RemoveOnDeath"));
}

// Called when the game starts or when spawned
void AAbilitySystemTestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAbilitySystemTestCharacter::AddCharacterAbilities()
{
	if(!AbilitySystemComponent.IsValid() || !AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		return;
	}

	for(TSubclassOf<UCharacterGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility,GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID),static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID),this));
	}

	AbilitySystemComponent->CharacterAbilitiesGiven=true;
	
}

void AAbilitySystemTestCharacter::InitializeAttributes()
{
	if(!AbilitySystemComponent.IsValid())
	{
		return;
	}

	if(!DefaultAttributes)
	{
		UE_LOG(LogTemp,Error,TEXT("%s() Missing DefaultAttribute for %s. Please fill in the character's blueprint"),*FString(__FUNCTION__), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes,GetCharacterLevel(),EffectContext);
	if(NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

//어트리뷰트를 추가하고, 새로운 Effect Context를  생성합니다.
void AAbilitySystemTestCharacter::AddStartupEffects()
{
	if(!AbilitySystemComponent.IsValid() || !AbilitySystemComponent->StartupEffectApplied)
	{
		return;
	}
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for(TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect,GetCharacterLevel(),EffectContext);
		if(NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}

	AbilitySystemComponent->StartupEffectApplied=true;
}

void AAbilitySystemTestCharacter::SetHealth(float Health)
{
	if(AttributeSetBase.IsValid())
	{
		AttributeSetBase->SetHealth(Health);
	}
}

void AAbilitySystemTestCharacter::SetMana(float Mana)
{
	if(AttributeSetBase.IsValid())
	{
		AttributeSetBase->SetHealth(Mana);
	}
}

bool AAbilitySystemTestCharacter::IsAlive() const
{
	return GetHealth()>0.0f;
}

int32 AAbilitySystemTestCharacter::GetAbilityLevel(AbilityID AbilityID) const
{
	return 1;
}

void AAbilitySystemTestCharacter::RemoveCharacterAbilities()
{
	if(!AbilitySystemComponent.IsValid() || !AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		return;
	}

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for(const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if((Spec.SourceObject==this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	for(int32 i =0; i<AbilitiesToRemove.Num();i++)
	{
			AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}

	AbilitySystemComponent->CharacterAbilitiesGiven=false;
}

void AAbilitySystemTestCharacter::Die()
{
	RemoveCharacterAbilities();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale=0;
	GetCharacterMovement()->Velocity=FVector(0);

	OnCharacterDied.Broadcast(this);

	if(AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAbilities();

		FGameplayTagContainer EffectsTagsToRemove;
		EffectsTagsToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectsEremoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectsTagsToRemove);
		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}

	if(DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
	}
	else
	{
		FinishDying();
	}
}

void AAbilitySystemTestCharacter::FinishDying()
{
	Destroy();
}

float AAbilitySystemTestCharacter::GetCharacterLevel() const
{
	if(AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetLevel();
	}
	return 0.0f;
}

float AAbilitySystemTestCharacter::GetHealth() const
{
	if(AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetHealth();
	}
	return 0.0f;
}

float AAbilitySystemTestCharacter::GetMaxHealth() const
{
	if(AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxHealth();
	}
	return 0.0f;
}

float AAbilitySystemTestCharacter::GetMana() const
{
	if(AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMana();
	}
	return 0.0f;
}

float AAbilitySystemTestCharacter::GetMaxMana() const
{
	if(AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxMana();
	}
	return 0.0f;
}

UAbilitySystemComponent* AAbilitySystemTestCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

