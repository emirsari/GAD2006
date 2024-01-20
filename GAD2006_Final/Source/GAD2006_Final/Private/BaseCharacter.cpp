// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter() : Health(0.0f), MaxHealth(0.0f), HealingRate(10.0f),
WalkingSpeed(250.0f), bDead(false)
{
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}

void ABaseCharacter::setHealth(float NewHealth)
{
	Health = NewHealth;
}

float ABaseCharacter::getHealth()
{
	return Health;
}

float ABaseCharacter::ModifyDamage_Implementation(float IncomingDamage)
{
	return IncomingDamage;
}


void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->bOrientRotationToMovement = true;

}

void ABaseCharacter::OnConstruction(const FTransform & Transform)
{
	Health = MaxHealth;
	Update = false;

}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bDead) {
		Health = FMath::Min(MaxHealth, Health + HealingRate * DeltaTime); // every second (each game tick) the character will be healed at some rate
	}

	if (Health <= 0 && !bDead) {
		bDead = true;
		// move this implementation to GameInstance, to trigger a set of events globally if the player dies
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController) DisableInput(PlayerController);

		PlayAnimMontage(DeathAnim, 1.0f);
		
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseCharacter::OnTimerEnd, 5.f, false);
	}

}
/*
float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
/*
	if (DamageAmount <= 0) return 0.f;

	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);
	return 0.0f;
	//
	
	if (bDead) return 0.f;
	DamageAmount = ModifyDamage(DamageAmount);
	Health -= DamageAmount;
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::White, FString::Printf(TEXT("Health: %f"), Health));

	if (Health <= 0.f) {
		bDead = true;
		//auto Player = Cast<APlayerController>(GetController());
		//if (Player != nullptr) DisableInput(Player);
		//OnPlayerDied();
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController) DisableInput(PlayerController);
	}

	return 0.0f;
	
}*/

void ABaseCharacter::OnTimerEnd()
{
	Destroy();
}
