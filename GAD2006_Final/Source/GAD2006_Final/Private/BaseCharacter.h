// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterType : uint8 
{
	CharT_Player = 0,
	CharT_Enemy = 1,
};

UCLASS()
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ABaseCharacter();

	UPROPERTY(VisibleAnywhere, Category = "SEM") 
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SEM")
	float MaxHealth;

	UFUNCTION(BlueprintCallable, Category = "SEM")
	virtual void setHealth(float NewHealth);

	UFUNCTION(BlueprintPure, Category = "SEM")
	float getHealth();

	UPROPERTY(EditAnywhere, Category = "SEM")
	bool Update;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SEM")
	float HealingRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SEM")
	float WalkingSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SEM")
	bool bDead;

	UFUNCTION(BlueprintNativeEvent, Category = "SEM") 
	float ModifyDamage(float IncomingDamage);

	UFUNCTION(BlueprintImplementableEvent, Category = "SEM") 
	float OnPlayerDied();

	UPROPERTY(EditAnywhere, Category = "SEM")
	UAnimMontage* DeathAnim;

protected:

	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:	

	virtual void Tick(float DeltaTime) override;
//	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private: 

	UPROPERTY(EditAnywhere, Category = "SEM")
	FTimerHandle TimerHandle;

	UFUNCTION()
	void OnTimerEnd();

};
