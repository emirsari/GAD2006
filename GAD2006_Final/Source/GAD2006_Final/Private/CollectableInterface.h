// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCollectable.h"
#include "CollectableInterface.generated.h"

/**
 * 
 */
UINTERFACE(BlueprintType)
class UCollectableInterface : public UInterface {
	GENERATED_BODY()
};

class ICollectableInterface {
	GENERATED_BODY()

public:

	//classes using this interface may implement ReactToMidnight
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "SAM")
	ECollectableType NotifyCollected();

};