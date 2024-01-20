// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCollectable.h"
#include "PlayerCharacter.h"


// Sets default values
ABaseCollectable::ABaseCollectable()
{

	// check if this time it works, if not try adding trigger volume to the scene

	RootComp = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));
	SetRootComponent(RootComp);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollectableStaticMesh"));
	StaticMesh->SetupAttachment(RootComp);
	StaticMesh->SetMobility(EComponentMobility::Movable);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(FName("SphereCollision"));
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);//
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);//
	SphereCollision->SetupAttachment(StaticMesh);
	SphereCollision->SetMobility(EComponentMobility::Movable);
	SphereCollision->SetGenerateOverlapEvents(true);

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(FName("RotatingMovement"));
	RotatingMovement->SetUpdatedComponent(StaticMesh);
	RotatingMovement->RotationRate = FRotator(0.f, 90.f, 0.f);

	//ConstructorHelpers::FObjectFinder<UStaticMesh> SetStaticMesh(
		//TEXT("/Game/StarterContent/Props/SM_Chair.SM_Chair")); can use this for assigning static mesh

	PrimaryActorTick.bCanEverTick = true;
	

}

void ABaseCollectable::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (!Cast<APlayerCharacter>(OtherActor)) return;

	APlayerCharacter* TempCharacter = Cast<APlayerCharacter>(OtherActor);
	if (TempCharacter->CharacterType == ECharacterType::CharT_Player) {
		Destroy();
	}
	
	/*APlayerCharacter* TempCharacter = Cast<APlayerCharacter>(OtherActor);

	if (TempCharacter->CharacterType == ECharacterType::CharT_Player && (TempCharacter->Health <= 75.0f))
	{
		TempCharacter->Health += HealthRestored;
		Destroy();
		//OverlappedComponent->GetAttachParentActor()->Destroy();
	}*/
}

// Called when the game starts or when spawned
void ABaseCollectable::BeginPlay()
{
	Super::BeginPlay();
	//SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseCollectable::OnBeginOverlap);
	
}

// Called every frame
void ABaseCollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

