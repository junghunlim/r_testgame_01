// Fill out your copyright notice in the Description page of Project Settings.


#include "Story_Mode_HUD.h"
#include "Blueprint/UserWidget.h"

AStory_Mode_HUD::AStory_Mode_HUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ui(TEXT("/Game/UI/BP_Story_Mode"));
	if (ui.Succeeded())
	{
		uiBPClass = ui.Class;
	}
}

void AStory_Mode_HUD::BeginPlay()
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
