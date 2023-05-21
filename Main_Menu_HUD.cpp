// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Menu_HUD.h"
#include "Blueprint/UserWidget.h"

AMain_Menu_HUD::AMain_Menu_HUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ui(TEXT("/Game/UI/BP_Main_Menu"));
	if (ui.Succeeded())
	{
		uiBPClass = ui.Class;
	}
}
void AMain_Menu_HUD::BeginPlay()
{
	Super::BeginPlay();
	if (uiBPClass)
	{
		uiWidget = CreateWidget<UUserWidget>(GetWorld(), uiBPClass);
		if (uiWidget)
		{
			uiWidget->AddToViewport();
		}
	}
}
