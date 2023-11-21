// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameSlot.generated.h"

// Forward Declarations
class AUnitBase; // to avoid circular dependency between classes AGameSlot & AUnitBase
// !!! NOTE: since forward declaration is used, remove one of the #include statements in either class.
// Instead, include the header in .cpp file of the class without the #include in its header file.
class ATBPlayerController;

// this struct will define our grid system. (column,row) data will be stored in the struct.
USTRUCT(Blueprintable)
struct FSGridPosition // F --> custom class, S --> structure (suggested naming)
{
	GENERATED_USTRUCT_BODY();

	FSGridPosition() { }
	FSGridPosition(uint8 col, uint8 row):
		Col(col),
		Row(row)
	{

	}

	UPROPERTY(EditAnywhere)
	uint8 Col; // can also be "int" but uint8 takes 1 byte and int takes 4 bytes. We do this to save storage space.

	UPROPERTY(EditAnywhere)
	uint8 Row;


};

UENUM(Blueprintable)
enum EGridState
{
	GS_Default,
	GS_Highlighted,
	GS_Offensive,
	GS_Supportive,
};

UCLASS()
class AGameSlot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameSlot();

	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Plane;

	UPROPERTY(BlueprintReadWrite)
	FSGridPosition GridPosition;

	UFUNCTION(BlueprintCallable)
	void SetState(EGridState NewState);

	UPROPERTY(VisibleAnywhere)
	AUnitBase* Unit;

	void SpawnUnitHere(TSubclassOf<AUnitBase>& UnitClass);

private:

	EGridState GridState;

	UFUNCTION()
	void OnGridClicked(AActor* TouchedActor, FKey ButtonPressed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
