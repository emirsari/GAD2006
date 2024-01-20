// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCollectable.h"
#include "PlayerCharacter.h"
#include "StaminaCollectable.generated.h"

/**
 * 
 */
UCLASS()
class AStaminaCollectable : public ABaseCollectable
{
	GENERATED_BODY()
	
public:

	AStaminaCollectable();

	UFUNCTION(BlueprintCallable, Category = "SEM")
	void RestoreStamina(AStaminaCollectable* OverlappedActor, APlayerCharacter* Target, float StaminaRestored);

protected:

	virtual void BeginPlay() override;

};
