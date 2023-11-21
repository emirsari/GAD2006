// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSlot.h"

/**
 * 
 */
class Command
{
public:
	Command();
	virtual ~Command() {};

	virtual void Execute() = 0;
	virtual void Revert() = 0;
	virtual void Update(float DeltaTime) {}; // animasyona baðlý zamanlý þeyler için 
	// (mesela animasyon olduðu sürece yürüme komutunda sayýlmasý gibi)
	virtual bool IsExecuting() { return false; };
	// update edilmesi gereken komutlarýn hala sürmekte olup olmadýðýna dair çek ediyoruz
};
