// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveCommand.h"
#include "GameGrid.h"
#include "UnitBase.h"
#include "GameManager.h"

MoveCommand::MoveCommand(FSGridPosition Src, FSGridPosition Dst) : Source(Src), Destination(Dst)
{
}

MoveCommand::~MoveCommand()
{
}

void MoveCommand::Execute()
{
	UE_LOG(LogTemp, Warning, TEXT("Executing MoveCommand..."));
	AGameSlot* SlotA = AGameGrid::FindSlot(Source);
	AGameSlot* SlotB = AGameGrid::FindSlot(Destination);

	AUnitBase* UnitA = SlotA->Unit;
	check(UnitA);
	UnitA->AssignToSlot(SlotB);
	SlotB->SetState(GS_Highlighted);
}

void MoveCommand::Revert()
{
	UE_LOG(LogTemp, Warning, TEXT("Reverting last move !"));
	AGameSlot* SlotA = AGameGrid::FindSlot(Destination);
	AGameSlot* SlotB = AGameGrid::FindSlot(Source);

	AUnitBase* UnitA = SlotA->Unit;
	check(UnitA);
	UnitA->AssignToSlot(SlotB);
	SlotA->SetState(GS_Default);
	
}
