// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBase.h"

// Sets default values
AUnitBase::AUnitBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AUnitBase::AssignToSlot(AGameSlot* NewSlot)
{
	check(NewSlot && NewSlot->Unit == nullptr); // "check" is a macro special to Unreal which throws an exception if the condition is false
	// kesinlikle true olmasý gereken þeylere "check" kullanýyoruz, böylece engine crash ettiðinde buradaki conditiondan dolayý mý kapandýðýný 
	// anlýyoruz

	if (Slot) Slot->Unit = nullptr;
	Slot = NewSlot;
	Slot->Unit = this;
	SetActorLocation(Slot->GetActorLocation() + StartOffset);
}

// Called when the game starts or when spawned
void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

