// Fill out your copyright notice in the Description page of Project Settings.


#include "TileGameManager.h"
#include "TilePlayerController.h"


// Sets default values
ATileGameManager::ATileGameManager() : GridSize(100), GridOffset(0,0,0.5f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	GridSelection = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridMesh"));
	GridSelection->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> 
		PlaneMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> 
		GridMaterial(TEXT("Material'/Game/UI/MAT_GridSlot.MAT_GridSlot'"));

	GridSelection->SetStaticMesh(PlaneMesh.Object);
	GridSelection->SetMaterial(0, GridMaterial.Object);
	GridSelection->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void ATileGameManager::BeginPlay()
{
	Super::BeginPlay();

	if (auto PlayerController = Cast<ATilePlayerController>(GWorld->GetFirstPlayerController()))
	{
		PlayerController->GameManager = this;
	}

	GridSelection->SetStaticMesh(TileTypes[CurrentTileIndex]->InstancedMesh->GetStaticMesh());
	GridSelection->SetRelativeScale3D(TileTypes[CurrentTileIndex]->InstancedMesh->GetRelativeScale3D());
	GridSelection->SetMaterial(0, TileTypes[CurrentTileIndex]->InstancedMesh->GetMaterial(0));
	
}

// Called every frame
void ATileGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileGameManager::OnActorInteraction(AActor* HitActor, FVector& Location, bool IsPressed)
{
	// Defined for controlling the rotation with RMB
	FRotator Rotation;
	Rotation.Yaw = 0.0f;
	Rotation.Pitch = 0.0f;
	Rotation.Roll = 0.0f;


	// No tile types ?
	if (TileTypes.Num() == 0) return;

	FVector GridLoc = GridOffset;
	GridLoc.X += FMath::GridSnap(Location.X, GridSize);
	GridLoc.Y += FMath::GridSnap(Location.Y, GridSize);
	GridLoc.Z += Location.Z;
		
	UPlayerInput* Input = GWorld->GetFirstPlayerController()->PlayerInput;

	if (Input->WasJustPressed(EKeys::LeftMouseButton))
	{
		int GridX = GridLoc.X / GridSize + MapExtendsInGrids;
		int GridY = GridLoc.Y / GridSize + MapExtendsInGrids;

		if (GridX < 0 || GridY < 0 || GridX >= MapExtendsInGrids * 2 || GridY >= MapExtendsInGrids * 2)
		{
			// Cannot place out of the grid
			return;
		}

		// Already a tile here ?
		if (Map[GridX][GridY] != nullptr) return;

		if (TileTypes.IsValidIndex(CurrentTileIndex))
		{
			ATileBase* SelectedTile = TileTypes[CurrentTileIndex];
			Map[GridX][GridY] = SelectedTile;

			FTransform TileTransform(GridLoc + GridOffset);
			SelectedTile->InstancedMesh->AddInstance(
				SelectedTile->InstancedMesh->GetRelativeTransform() * TileTransform, true);

		}

		UE_LOG(LogTemp, Warning, TEXT("Hit: %s - %f, %f, %f"), HitActor ? *HitActor->GetActorLabel() : TEXT("None"),
			Location.X, Location.Y, Location.Z);

		
	}
	else if(Input->WasJustPressed(EKeys::MouseScrollDown))
	{
		CurrentTileIndex = (CurrentTileIndex + 1) % TileTypes.Num();
		UE_LOG(LogTemp, Warning, TEXT("TileType: %s "), *TileTypes[CurrentTileIndex]->GetActorLabel());


		// Displays currently selected tile in real-time.
		GridSelection->SetStaticMesh(TileTypes[CurrentTileIndex]->InstancedMesh->GetStaticMesh());
		GridSelection->SetRelativeScale3D(TileTypes[CurrentTileIndex]->InstancedMesh->GetRelativeScale3D());
		GridSelection->SetMaterial(0, TileTypes[CurrentTileIndex]->InstancedMesh->GetMaterial(0));

	}
	else if (Input->WasJustPressed(EKeys::MouseScrollUp))
	{
		// Prevent negative values (array index out of bounds error)
		CurrentTileIndex = (CurrentTileIndex - 1 + TileTypes.Num()) % TileTypes.Num();
		UE_LOG(LogTemp, Warning, TEXT("TileType: %s "), *TileTypes[CurrentTileIndex]->GetActorLabel());

		// Displays currently selected tile in real-time.
		GridSelection->SetStaticMesh(TileTypes[CurrentTileIndex]->InstancedMesh->GetStaticMesh());
		GridSelection->SetRelativeScale3D(TileTypes[CurrentTileIndex]->InstancedMesh->GetRelativeScale3D());
		GridSelection->SetMaterial(0, TileTypes[CurrentTileIndex]->InstancedMesh->GetMaterial(0));
	}
	else if (Input->WasJustPressed(EKeys::RightMouseButton))
	{
		
		// Rotate when RMB clicked
		Rotation.Yaw = Rotation.Yaw + 90.0f;

		FTransform RelativeTransform = TileTypes[CurrentTileIndex]->InstancedMesh->GetRelativeTransform();
		FTransform RotationTransform = FTransform(FRotator(0.0, Rotation.Yaw, 0.0));

		GridSelection->SetRelativeTransform(RotationTransform * RelativeTransform);

	}
	else
	{
		GridSelection->SetWorldLocation(GridLoc + GridOffset);

	}
		
	

		
	
}

