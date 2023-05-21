// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerTurnChangedDelegate, bool);

UCLASS()
class R_TESTGAME_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	FOnPlayerTurnChangedDelegate OnPlayerTurnChanged;

	AMyPlayerController();

	//명령위젯 보여주기
	void ShowOrderWidget();

	void ShowGameScoreWidgetWin();
	void ShowGameScoreWidgetLose();
	void ShowGameScoreWidgetDraw();

	void quitgame();
	//class UOrderWidget* GetHUDWidget() const;

	bool bClickLeftMouse;

	//FVector2D InitialMousePosition;

	//FVector2D CurrentMousePosition;

	UFUNCTION()
	void MoveRR(FVector2D MouseDelta);

	void StartTurn();

	void EndTurn();

	void CheckGameScore();

	void RemoveOrderWidget();

protected:

	void InputLeftMouseButtonPressed();

	void InputLeftMouseButtonReleased();

	virtual void SetupInputComponent() override;

	virtual void PlayerTick(float DeltaTime) override;
	
	virtual void BeginPlay() override;

	//명령위젯 불러오기위한~
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UOrderWidget> OrderWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UOrderWidget* OrderWidget;

	//메인HUD위젯 불러오기위한~
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UHUDWidget> HUDWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UHUDWidget* CurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UGameScoreWidget> GameScoreWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UGameScoreWidget* CurrentGameScoreWidget;

private:

	void SetMyTurn(bool myturn);

};