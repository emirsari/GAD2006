// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthCollectable.h"

AHealthCollectable::AHealthCollectable(){

	CollectableType = ECollectableType::CollT_HealthCollectable;
	PrimaryActorTick.bCanEverTick = true;
}


void AHealthCollectable::RestoreHealth(AHealthCollectable* OverlappedActor, APlayerCharacter* Target, float HealthRestored)
{
	if (Target->Health <= 75) {
		Target->setHealth(Target->Health + HealthRestored);

		OverlappedActor->Destroy();
	}
}

void AHealthCollectable::BeginPlay()
{
	Super::BeginPlay();
	
}

