// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"

//rrstate (rr1,rr2,rr3 해서 지정해주기)
FPlayerRRInfo rr_1;
FPlayerRRInfo rr_2;
FPlayerRRInfo rr_3;


AMyPlayerState::AMyPlayerState()
{
	PlayerName = FText::FromString("Name");
	PlayerLevel = 1;
	PlayerTier = 1;

	//rr1 info
	rr_1.RRClass = FText::FromString("nono");
	rr_1.RRLevel = 1;
	
	rr_2.RRClass = FText::FromString("nono2");
	rr_2.RRLevel = 2;

	rr_3.RRClass = FText::FromString("nono3");
	rr_3.RRLevel = 3;

}

int32 AMyPlayerState::GetPlayerLevel()
{
	return PlayerLevel;
}

int32 AMyPlayerState::GetPlayerTier()
{
	return PlayerTier;
}

FText AMyPlayerState::GetPlayerName()
{
	return PlayerName;
}

int32 AMyPlayerState::GetRRLevel1()
{
	return rr_1.RRLevel;
}

FText AMyPlayerState::GetRRClass1()
{
	return rr_1.RRClass;
}

UTexture2D* AMyPlayerState::GetRRThumbnail1()
{
	return rr_1.RRThumbnail;
}

int32 AMyPlayerState::GetRRLevel2()
{
	return rr_2.RRLevel;
}

FText AMyPlayerState::GetRRClass2()
{
	return rr_2.RRClass;
}

UTexture2D* AMyPlayerState::GetRRThumbnail2()
{
	return rr_2.RRThumbnail;
}

int32 AMyPlayerState::GetRRLevel3()
{
	return rr_3.RRLevel;
}

FText AMyPlayerState::GetRRClass3()
{
	return rr_3.RRClass;
}

UTexture2D* AMyPlayerState::GetRRThumbnail3()
{
	return rr_3.RRThumbnail;
}

void AMyPlayerState::InitPlayerData()
{
	PlayerName = FText::FromString("limlim2");
	PlayerLevel = 5;
	PlayerTier = 10;
}

//rrstate
void AMyPlayerState::InitPlayerRRData()
{
	rr_1.RRClass = FText::FromString("CAT_1");
	rr_1.RRLevel = 1;
	rr_1.RRThumbnail = LoadObject<UTexture2D>(NULL, TEXT("/Game/Image/t_cat01.t_cat01"), NULL, LOAD_None, NULL);
	
	rr_2.RRClass = FText::FromString("BEAR_2");
	rr_2.RRLevel = 2;
	rr_2.RRThumbnail = LoadObject<UTexture2D>(NULL, TEXT("/Game/Image/t_bear01.t_bear01"), NULL, LOAD_None, NULL);

	rr_3.RRClass = FText::FromString("EAGLE_3");
	rr_3.RRLevel = 3;
	rr_3.RRThumbnail = LoadObject<UTexture2D>(NULL, TEXT("/Game/Image/t_eagle01.t_eagle01"), NULL, LOAD_None, NULL);

}