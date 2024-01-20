// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NetGameState.generated.h"

class ANetPlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVictory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRestart);

/**
 * 
 */
UCLASS()
class ANetGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	ANetGameState();

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Winner)
	int WinningPlayer;

	UFUNCTION()
	void OnRep_Winner();

	UPROPERTY(BlueprintAssignable)
	FOnVictory OnVictory;

	UPROPERTY(BlueprintAssignable)
	FOnRestart OnRestart;

	UFUNCTION(NetMulticast, Reliable)
	void TriggerRestart();

	UFUNCTION(BlueprintCallable)
	ANetPlayerState* GetPlayerStateByIndex(int PlayerIndex);

	UPROPERTY()
	FTimerHandle TimerHandleForWinCondition; 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Countdown; 

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_TimeLeft)
	float TimeLeft; 

	UFUNCTION(BlueprintCallable)
	void BeginCountdown();

	UFUNCTION()
	void UpdateCountdown(); 

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCountdownNotification(); 

	UFUNCTION(NetMulticast, Reliable)
	void EndCountdown(); 

	UFUNCTION()
	void OnRep_TimeLeft();

};


