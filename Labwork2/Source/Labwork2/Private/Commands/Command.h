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
	virtual void Update(float DeltaTime) {}; // animasyona ba�l� zamanl� �eyler i�in 
	// (mesela animasyon oldu�u s�rece y�r�me komutunda say�lmas� gibi)
	virtual bool IsExecuting() { return false; };
	// update edilmesi gereken komutlar�n hala s�rmekte olup olmad���na dair �ek ediyoruz
};
