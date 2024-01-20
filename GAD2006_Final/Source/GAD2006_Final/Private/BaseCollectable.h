// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "BaseCollectable.generated.h"

UENUM(BlueprintType)
enum class ECollectableType : uint8
{
	CollT_CollectableItem_1 = 0,
	CollT_HealthCollectable = 1,
	CollT_StaminaCollectable = 2,
	CollT_SpeedCollectable = 3,
};

USTRUCT(BlueprintType)
struct FSCollectableInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CollectedAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAmount;

};

UCLASS()
class ABaseCollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCollectable();

	UPROPERTY(VisibleAnywhere, Category = "SEM")
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, Category = "SEM")
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SEM")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "SEM")
	URotatingMovementComponent* RotatingMovement;

	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "SEM")
	ECollectableType CollectableType;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
