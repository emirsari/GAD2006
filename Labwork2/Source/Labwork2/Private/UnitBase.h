// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameSlot.h"
#include "UnitBase.generated.h"

// Forward Declarations
class AGameSlot; // to avoid circular dependency between classes AGameSlot & AUnitBase

UCLASS()
class AUnitBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitBase();

	void AssignToSlot(AGameSlot* NewSlot); // Slot-unit baðýntýsýný kurmada kullanýcaz

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure)
	bool IsControlledByThePlayer(); // no need for body for implementable events

	UPROPERTY(EditAnywhere)
	FVector StartOffset;

	UPROPERTY(VisibleAnywhere) // Slot-unit baðýntýsýný kurmada kullanýcaz
	AGameSlot* Slot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
