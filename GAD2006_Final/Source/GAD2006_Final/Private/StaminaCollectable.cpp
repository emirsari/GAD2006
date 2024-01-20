// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaCollectable.h"

AStaminaCollectable::AStaminaCollectable()
{
	CollectableType = ECollectableType::CollT_StaminaCollectable;
	PrimaryActorTick.bCanEverTick = true;
}



void AStaminaCollectable::RestoreStamina(AStaminaCollectable* OverlappedActor, APlayerCharacter* Target, float StaminaRestored)
{
	if (Target->getStamina() <= 50) {
		Target->setStamina(Target->getStamina() + StaminaRestored);

		OverlappedActor->Destroy();

	}
}

void AStaminaCollectable::BeginPlay()
{
	Super::BeginPlay();
}
