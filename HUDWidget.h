// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class R_TESTGAME_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void BindPlayerState(class AMyPlayerState* PlayerState);

	void BindPlayerTurnState(class AMyPlayerController* playercontroller);

	virtual void NativeConstruct() override;
	
	void UpdatePlayerState();
	
	void UpdatePlayerTurnState(bool myturn);

	TWeakObjectPtr<class AMyPlayerState> CurrentPlayerState;

	TWeakObjectPtr<class AMyPlayerController> CurrentPlayerController;
	
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "UI_HUD", meta = (BindWidget))
	class UTextBlock* PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "UI_HUD", meta = (BindWidget))
	class UTextBlock* PlayerTier;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "UI_HUD", meta = (BindWidget))
	class UTextBlock* PlayerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "UI_HUD", meta = (BindWidget))
	class UTextBlock* PlayerTurnState;

};
