// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCollectable.h"
#include "PlayerCharacter.h"
#include "CollectableItem1.generated.h"

/**
 * 
 */
UCLASS()
class ACollectableItem1 : public ABaseCollectable
{
	GENERATED_BODY()
	
public:

	ACollectableItem1();

	UFUNCTION(BlueprintCallable, Category = "SEM")
	void CollectItem(ACollectableItem1* OverlappedActor, APlayerCharacter* Target);

protected:

	virtual void BeginPlay() override;
};
