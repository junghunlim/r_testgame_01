// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Main_Menu_HUD.generated.h"

/**
 * 
 */
UCLASS()
class R_TESTGAME_API AMain_Menu_HUD : public AHUD
{
	GENERATED_BODY()

public:
	AMain_Menu_HUD();

	void virtual BeginPlay() override;

private:
	TSubclassOf<class UUserWidget> uiBPClass;
	UUserWidget* uiWidget;

};
