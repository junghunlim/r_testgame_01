// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Story_Mode_HUD.generated.h"

/**
 * 
 */
UCLASS()
class R_TESTGAME_API AStory_Mode_HUD : public AHUD
{
	GENERATED_BODY()

public:
	AStory_Mode_HUD();

	void virtual BeginPlay() override;

private:
	TSubclassOf<class UUserWidget> uiBPClass;
	UUserWidget* uiWidget;

};
