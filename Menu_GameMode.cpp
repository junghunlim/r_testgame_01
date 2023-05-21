// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu_GameMode.h"
#include "Main_Menu_HUD.h"

AMenu_GameMode::AMenu_GameMode()
{
	HUDClass = AMain_Menu_HUD::StaticClass();
	DefaultPawnClass = nullptr;
	//PlayerControllerClass = ;

}