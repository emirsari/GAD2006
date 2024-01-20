// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BaseTrap.generated.h"

UCLASS()
class ABaseTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTrap();

	UPROPERTY(VisibleAnywhere, Category = "SEM")
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, Category = "SEM")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, Category = "SEM")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SEM")
	float TrapDamageAmount;

	UFUNCTION(BlueprintCallable, Category = "SAM")
	void DamagePlayer(float DamageAmount, APlayerCharacter* DamagedActor);
	/*
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
