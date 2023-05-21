// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "OrderWidget.generated.h"

/**
 * 
 */
UCLASS()
class R_TESTGAME_API UOrderWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "UI_HUD", meta = (BindWidget))
	UButton* Btn_Move;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "UI_HUD", meta = (BindWidget))
	UButton* Btn_Skill;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "UI_HUD", meta = (BindWidget))
	UButton* Btn_Back;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UOrderWidget* OrderWidget;

	UFUNCTION()
	void Btn_Move_Cliked();

	UFUNCTION()
	void Btn_Skill_Cliked();

	UFUNCTION()
	void Btn_Back_Cliked();

	void BindRRState(class ABasic_RR* RRState);

	virtual void NativeConstruct() override;

	void UpdateRRState();

	TWeakObjectPtr<class ABasic_RR> Basic_RRState;


	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "UI_HUD", meta = (BindWidget))
	class UTextBlock* RRClass;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "UI_HUD", meta = (BindWidget))
	class UTextBlock* RRLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI_HUD", meta = (BindWidget))
	class UImage* RRThumbnail;

};
