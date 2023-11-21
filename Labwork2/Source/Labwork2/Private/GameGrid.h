// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ChildActorComponent.h"
#include "Components/BoxComponent.h"
#include "GameSlot.h"
#include "GameGrid.generated.h"

UCLASS()
class AGameGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameGrid();

	virtual void OnConstruction(const FTransform& Transform) override;

	// referencing class types : UClass* (class type of all classes)
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGameSlot> GridClass; // creates a reference to this class

	UPROPERTY(EditAnywhere)
	int NumRows;

	UPROPERTY(EditAnywhere)
	int NumCols;
	
	UPROPERTY(VisibleAnywhere)
	TArray<UChildActorComponent*> GridActors;// a component that automatically creates an actor on the scene

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AGameSlot* GetSlot(FSGridPosition& Position); // const FSGridPosition& Position daha doðru bir implementation,
	// deðiþkene sadece eriþileceðini fakat deðiþtirilmeyeceðini söylüyor
	// '&' --> structure'ýn adresini vererek yükü azaltýyor (structure içindeki her þeyi çaðýrmak yerine ihtiyacýmýz olaný çaðýrýyoruz)
	static AGameSlot* FindSlot(FSGridPosition Position);

private:

	static AGameGrid* GameGrid; 
	// we make it static since we assume that the existing game grid will be the only game grid.

};
