// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableItem1.h"

ACollectableItem1::ACollectableItem1() {

	CollectableType = ECollectableType::CollT_CollectableItem_1;
	PrimaryActorTick.bCanEverTick = true;
}

void ACollectableItem1::CollectItem(ACollectableItem1* OverlappedActor, APlayerCharacter* Target)
{
	Target->CollectedItemAmount += 1;
	OverlappedActor->Destroy();
}

void ACollectableItem1::BeginPlay()
{
	Super::BeginPlay();
}
