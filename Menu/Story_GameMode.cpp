// Fill out your copyright notice in the Description page of Project Settings.


#include "Story_GameMode.h"
#include "Story_Mode_HUD.h"

AStory_GameMode::AStory_GameMode()
{
	HUDClass = AStory_Mode_HUD::StaticClass();
	DefaultPawnClass = nullptr;
	//PlayerControllerClass = ;

}
