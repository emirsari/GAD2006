// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "SAMEnemyCharacter.generated.h"

/**
 *
 * NOTE: Accidentaly named it SAM, instead of SEM.
 * This is a replacement class for the old "EnemyCharacter" class, it needed reparenting due to implementation changes.
 */
UCLASS()
class ASAMEnemyCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:

	ASAMEnemyCharacter();

};
