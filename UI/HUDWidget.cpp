// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "MyPlayerState.h"
#include "MyPlayerController.h"
#include "Components/TextBlock.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("playername")));

	PlayerTier = Cast<UTextBlock>(GetWidgetFromName(TEXT("playertier")));

	PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("playerlevel")));

	PlayerTurnState = Cast<UTextBlock>(GetWidgetFromName(TEXT("playerturnstate")));
}

void UHUDWidget::BindPlayerState(class AMyPlayerState* PlayerState)
{
	CurrentPlayerState = PlayerState;
	PlayerState->OnPlayerStateChanged.AddUObject(this, &UHUDWidget::UpdatePlayerState);
}


void UHUDWidget::UpdatePlayerState()
{
	PlayerName->SetText(CurrentPlayerState->GetPlayerName());
	PlayerTier->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetPlayerTier())));
	PlayerLevel->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetPlayerLevel())));
}


void UHUDWidget::BindPlayerTurnState(AMyPlayerController* playercontroller)
{
	CurrentPlayerController = playercontroller;
	playercontroller->OnPlayerTurnChanged.AddUObject(this, &UHUDWidget::UpdatePlayerTurnState);
}


void UHUDWidget::UpdatePlayerTurnState(bool myturn)
{
	if (myturn == true)
	{
		PlayerTurnState->SetText(FText::FromString("Your Turn"));
	}
	else
	{
		PlayerTurnState->SetText(FText::FromString("Waiting"));
	}
}

