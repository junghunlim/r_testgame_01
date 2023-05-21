// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "StoryModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class R_TESTGAME_API UStoryModeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_rat_map_01;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_rat_map_02;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_rat_map_03;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_rat_map_04;

	UFUNCTION()
		void Btn_01_Cliked();

	UFUNCTION()
		void Btn_02_Cliked();

	UFUNCTION()
		void Btn_03_Cliked();

	UFUNCTION()
		void Btn_04_Cliked();

};
