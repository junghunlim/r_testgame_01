// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Main_Menu_Widget.generated.h"

/**
 * 
 */
UCLASS()
class R_TESTGAME_API UMain_Menu_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_VS;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_StoryMode;

	UFUNCTION()
	void Btn_VS_Cliked();

	UFUNCTION()
	void Btn_StoryMode_Cliked();
};
