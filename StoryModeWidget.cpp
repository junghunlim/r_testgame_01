// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryModeWidget.h"
#include <Kismet/GameplayStatics.h>

void UStoryModeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_rat_map_01)
	{
		Btn_rat_map_01->OnClicked.AddDynamic(this, &UStoryModeWidget::Btn_01_Cliked);
	}

	if (Btn_rat_map_02)
	{
		Btn_rat_map_02->OnClicked.AddDynamic(this, &UStoryModeWidget::Btn_02_Cliked);
	}

	if (Btn_rat_map_03)
	{
		Btn_rat_map_03->OnClicked.AddDynamic(this, &UStoryModeWidget::Btn_03_Cliked);
	}

	if (Btn_rat_map_04)
	{
		Btn_rat_map_04->OnClicked.AddDynamic(this, &UStoryModeWidget::Btn_04_Cliked);
	}

}

void UStoryModeWidget::Btn_01_Cliked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/Map/Tutorial_01");
}

void UStoryModeWidget::Btn_02_Cliked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/Map/Tutorial_2");
}

void UStoryModeWidget::Btn_03_Cliked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/Map/Tutorial_3");
}

void UStoryModeWidget::Btn_04_Cliked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/Map/Tutorial_4");
}
