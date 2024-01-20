// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCollectable.h"
#include "PlayerCharacter.h"
#include "TimerManager.h"
#include "SpeedCollectable.generated.h"

/**
 * 
 */
UCLASS()
class ASpeedCollectable : public ABaseCollectable
{
	GENERATED_BODY()
	
public:

	ASpeedCollectable();

	UFUNCTION(BlueprintCallable, Category = "SEM")
	void BoostRunSpeed(ASpeedCollectable* OverlappedActor, APlayerCharacter* Target, float SpeedBoostAmount);

protected:

	virtual void BeginPlay() override;

};
