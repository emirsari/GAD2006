// Fill out your copyright notice in the Description page of Project Settings.


#include "NetGameState.h"
#include "NetPlayerState.h"
#include "NetBaseCharacter.h"
#include "Net/UnrealNetwork.h"
#include "NetGameMode.h"

ANetGameState::ANetGameState() : WinningPlayer(-1)
{
	Countdown = 30.0f; // Blue team win condition, 30 secs
	TimeLeft = Countdown; // setting remaining time to notify server if countdown is reached
}

void ANetGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANetGameState, WinningPlayer);
	DOREPLIFETIME_CONDITION(ANetGameState, TimeLeft, COND_OwnerOnly); // notify server of remaining time replicated variable 

}

void ANetGameState::OnRep_Winner()
{
	if (WinningPlayer >= 0) {
		OnVictory.Broadcast();
	}
}

void ANetGameState::TriggerRestart_Implementation()
{
	OnRestart.Broadcast();
}

ANetPlayerState* ANetGameState::GetPlayerStateByIndex(int PlayerIndex)
{
	for (APlayerState* PS : PlayerArray)
	{
		ANetPlayerState* State = Cast<ANetPlayerState>(PS);
		if (State && State->PlayerIndex == PlayerIndex)
		{
			return State;
		}
	}
	return nullptr;
}


void ANetGameState::BeginCountdown()
{
	TimeLeft = Countdown; // start countdown by specified value
	GetWorld()->GetTimerManager().SetTimer(TimerHandleForWinCondition, this, &ANetGameState::UpdateCountdown, 1.0f, true);
	// every second, call "UpdateCountdown" function to update the countdown on server.
}

void ANetGameState::EndCountdown_Implementation()
{
	// clear timer for clients 
	GetWorld()->GetTimerManager().ClearTimer(TimerHandleForWinCondition);
}

void ANetGameState::UpdateCountdown()
{
	UpdateCountdownNotification();
	if (!(TimeLeft <= 0))
	{
		TimeLeft--; // decrease remaining time until the countdown is reached 
		GEngine->AddOnScreenDebugMessage(0, 2.5f, FColor::Green, FString::Printf(TEXT("Time left: %f"), TimeLeft));
	}
	else
	{
		ANetGameMode* GameModeReference = Cast<ANetGameMode>(GetWorld()->GetAuthGameMode());
		if (GameModeReference)
		{
			GameModeReference->CountdownFinished(); // when countdown reaches zero, trigger the win
		}
	}
}

void ANetGameState::OnRep_TimeLeft()
{
	UpdateCountdownNotification(); //replicate TimeLeft to clients
}


