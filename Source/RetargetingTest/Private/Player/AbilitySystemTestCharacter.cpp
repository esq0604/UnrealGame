// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Player/AbilitySystemTestCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RetargetingTest/Public/Ability/CharacterAbilitySystemComponent.h"
#include "RetargetingTest/Public/Attribute/CharacterAttributeSetBase.h"

// Sets default values
AAbilitySystemTestCharacter::AAbilitySystemTestCharacter()
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

		FGameplayTagContainer EFfects
	}
}

void AAbilitySystemTestCharacter::FinishDying()
{
	Destroy();
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
}

// Called every frame
void AAbilitySystemTestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAbilitySystemTestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AAbilitySystemTestCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

