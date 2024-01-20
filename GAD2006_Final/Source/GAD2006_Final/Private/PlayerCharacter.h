// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	APlayerCharacter();

	UPROPERTY(EditAnywhere, Category = "SEM")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "SEM")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SEM")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SEM")
	float CrouchingSpeed;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "SEM")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SEM")
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, Category = "SEM")
	float StaminaGainRate;

	UFUNCTION(BlueprintPure, Category = "SEM")
	float getStamina();

	UFUNCTION(BlueprintCallable, Category = "SEM")
	void setStamina(float NewStamina);

	UFUNCTION(BlueprintPure, Category = "SEM")
	float getMaxStamina();

	void setHealth(float NewPlayerHealth) override;

	UPROPERTY(EditAnywhere, Category = "SEM")
	UAnimMontage* LightAttackMontage_1;

	UPROPERTY(EditAnywhere, Category = "SEM")
	UAnimMontage* LightAttackMontage_2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SEM")
	ECharacterType CharacterType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SEM")
	bool bGettingHit;

	UPROPERTY(EditAnywhere, Category = "SEM")
	UAnimMontage* HitReactionAnim;

	UFUNCTION(BlueprintImplementableEvent, Category = "SEM")
	void HitReact();
	void HitReact_Implementation(APlayerCharacter* HitActor);

	UFUNCTION(BlueprintCallable, Category = "SEM")
	void HitDetect();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SEM")
	bool bBlocking;

	UFUNCTION(BlueprintCallable)
		void DoLightAttack(float AnimPlayRate, float AnimRetriggerDelay,
			UAnimMontage* AnimInstance_1, UAnimMontage* AnimInstance_2, int AnimCount);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SEM")
	int CollectedItemAmount;


private: 

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void RunPressed();
	void RunReleased();

	void JumpPressed();
	void CrouchPressed();

	UFUNCTION(BlueprintCallable)
	void LightAttackPressed();

	void HeavyAttackPressed();
	void BlockPressed();
	void BlockReleased();
	
	void UpdateMovementParams();

	UPROPERTY(VisibleAnywhere, Category = "SEM")
	float Stamina;

	UPROPERTY(VisibleAnywhere, Category = "SEM")
	bool bHoldingRunKey;

	UPROPERTY(VisibleAnywhere, Category = "SEM")
	bool bStaminaDrained;

	UPROPERTY(VisibleAnywhere, Category = "SEM")
	bool bReleased;

	UPROPERTY(VisibleAnywhere, Category = "SEM")
	bool bAttacking;

	// variable to imitate the behavior of FlipFlop node
	UPROPERTY(VisibleAnywhere, Category = "SEM")
	bool bPressedCrouchKey;

	UPROPERTY(EditAnywhere, Category = "SEM")
	FTimerHandle TimerHandle_PlayerCharacter;

	UFUNCTION()
	void OnTimerEnd_Attack();

	UFUNCTION()
	void OnTimerEnd_HitReact();

	void DoHeavyAttack(float AnimPlayRate, float AnimRetriggerDelay,
	UAnimMontage* AnimInstance);

	UPROPERTY(EditAnywhere, Category = "SEM")
	UAnimMontage* HeavyAttackAnim;

};
