// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTrap.h"
#include "PlayerCharacter.h"

// Sets default values
ABaseTrap::ABaseTrap()
{
	RootComp = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));
	SetRootComponent(RootComp);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollectableStaticMesh"));
	StaticMesh->SetupAttachment(RootComp);
	StaticMesh->SetMobility(EComponentMobility::Movable);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	BoxCollision->SetupAttachment(RootComp); // changed from StaticMesh to see how it will affect OverlapEvent
	BoxCollision->SetMobility(EComponentMobility::Movable);
	BoxCollision->SetGenerateOverlapEvents(true);

	//ConstructorHelpers::FObjectFinder<UStaticMesh> SetStaticMesh(
		//TEXT("/Game/StarterContent/Props/SM_Chair.SM_Chair")); can use this for assigning static mesh

	PrimaryActorTick.bCanEverTick = true;
	//BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseTrap::OnBoxBeginOverlap);
}


void ABaseTrap::DamagePlayer(float DamageAmount, APlayerCharacter* DamagedActor)
{
	// call this function from OnBeginOverlap
	DamagedActor->Health -= DamageAmount;
}
/*
void ABaseTrap::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* OverlappedActor = Cast<APlayerCharacter>(OtherActor);
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::Printf(TEXT("Player Hit !")));
	DamagePlayer(TrapDamageAmount, OverlappedActor);
}*/

// Called when the game starts or when spawned
void ABaseTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

