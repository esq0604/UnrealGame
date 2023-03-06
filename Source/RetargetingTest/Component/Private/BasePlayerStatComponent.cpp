// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/BasePlayerStatComponent.h"


// Sets default values for this component's properties
UBasePlayerStatComponent::UBasePlayerStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent=true;
	AttackDamage=10.0f;
	MaxHp=100.0f;
	NewHpPercent=1;
	CurrentHp=MaxHp;
	
}






