// Fill out your copyright notice in the Description page of Project Settings.


#include "GameScoreWidget.h"
#include "Components/TextBlock.h"

void UGameScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("gamescore")));

}

void UGameScoreWidget::SetGameScoreWin()
{
	GameScore->SetText(FText::FromString(" WIN "));
}

void UGameScoreWidget::SetGameScoreLose()
{
	GameScore->SetText(FText::FromString(" LOSE "));
}

void UGameScoreWidget::SetGameScoreDraw()
{
	GameScore->SetText(FText::FromString(" DRAW "));
}
