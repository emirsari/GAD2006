// Fill out your copyright notice in the Description page of Project Settings.


#include "GameGrid.h"

//Global reference to the gamegrid 
AGameGrid* AGameGrid::GameGrid = nullptr;
// class değişkenleri her zaman global scopeda initialize edilmek zorunda, yoksa hata verir
// Sets default values
AGameGrid::AGameGrid() : NumRows(8), NumCols(8)
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	GameGrid = this; // Singleton
}


void AGameGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	for (auto Grid : GridActors)
	{
		Grid->DestroyComponent();
	}

	GridActors.Empty();

	if (!GridClass->IsValidLowLevel()) return;

	AGameSlot* Slot = GridClass->GetDefaultObject<AGameSlot>(); // get a default slot for placement

	if (Slot == nullptr) return;

	FVector Extends = Slot->Box->GetScaledBoxExtent() * 2;

	for (int i = 0; i < NumRows; i++) {
		for (int j = 0; j < NumCols; j++) {
			FName GridName(FString::Printf(TEXT("Slot%dx%d"), j, i));
			auto Grid = NewObject<UChildActorComponent>(this, UChildActorComponent::StaticClass(), GridName);
			Grid->RegisterComponent();
			Grid->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			Grid->SetRelativeLocation(FVector((NumRows - i - 1) * Extends.X - (NumRows * 0.5f - 0.5f) * Extends.X, j * Extends.Y - (NumCols * 0.5f - 0.5f) * Extends.Y, 0)); 

			GridActors.Add(Grid);

			Grid->SetChildActorClass(GridClass);
			AGameSlot* GameSlot = Cast<AGameSlot>(Grid->GetChildActor());

			GameSlot->SetActorLabel(GridName.ToString());
			GameSlot->GridPosition.Col = j;
			GameSlot->GridPosition.Row = i;


		}
	}

}

// Called when the game starts or when spawned
void AGameGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AGameSlot* AGameGrid::GetSlot(FSGridPosition& Position)
{
	int GridIndex = Position.Row * NumCols + Position.Col; // we convert the raw coordinates to array indexes with this calculation (like in matrices)

	if (GridActors.IsValidIndex(GridIndex)) {
		return Cast<AGameSlot>(GridActors[GridIndex]->GetChildActor());
	}
	return nullptr;
}

AGameSlot* AGameGrid::FindSlot(FSGridPosition Position)
{
	if (GameGrid) { // != nullptr test ediyoruz aslında
		return GameGrid->GetSlot(Position);
	}
	return nullptr;
}

