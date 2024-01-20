// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCollectable.h"
#include "PlayerCharacter.h"
#include "HealthCollectable.generated.h"

/**
 * 
 */
UCLASS()
class AHealthCollectable : public ABaseCollectable
{
	GENERATED_BODY()

public:

	AHealthCollectable();

	UFUNCTION(BlueprintCallable, Category = "SEM")
	void RestoreHealth(AHealthCollectable* OverlappedActor, APlayerCharacter* Target, float HealthRestored);

protected:
	
	virtual void BeginPlay() override;	
	
};
