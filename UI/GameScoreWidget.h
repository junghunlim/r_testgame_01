// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class R_TESTGAME_API UGameScoreWidget : public UUserWidget
{
	GENERATED_BODY()



public:

	virtual void NativeConstruct() override;

	void SetGameScoreWin();

	void SetGameScoreLose();

	void SetGameScoreDraw();

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "UI_HUD", meta = (BindWidget))
	class UTextBlock* GameScore;
	
};
