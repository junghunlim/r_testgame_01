// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Menu_Widget.h"
#include <Kismet/GameplayStatics.h>

void UMain_Menu_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_VS)
	{
		Btn_VS->OnClicked.AddDynamic(this, &UMain_Menu_Widget::Btn_VS_Cliked);
	}

	if (Btn_StoryMode)
	{
		Btn_StoryMode->OnClicked.AddDynamic(this, &UMain_Menu_Widget::Btn_StoryMode_Cliked);
	}

}
//
void UMain_Menu_Widget::Btn_VS_Cliked()
{
	//°ÔÀÓÁ¾·á
	APlayerController* controller1 = GetWorld()->GetFirstPlayerController();
	controller1->ConsoleCommand("quit");
}

void UMain_Menu_Widget::Btn_StoryMode_Cliked()
{
	//½ºÅä¸® ¸ðµå
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/Map/Story_Mode");

}
