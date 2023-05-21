// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

USTRUCT(Atomic, BlueprintType)
struct FPlayerRRInfo
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText RRClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* RRThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RRLevel;

};

UCLASS()
class R_TESTGAME_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

	AMyPlayerState();
	
	void InitPlayerData();
	void InitPlayerRRData();
	
	int32 GetPlayerLevel();
	int32 GetPlayerTier();
	FText GetPlayerName();

	//rrinfo
	int32 GetRRLevel1();
	FText GetRRClass1();
	UTexture2D* GetRRThumbnail1();

	int32 GetRRLevel2();
	FText GetRRClass2();
	UTexture2D* GetRRThumbnail2();

	int32 GetRRLevel3();
	FText GetRRClass3();
	UTexture2D* GetRRThumbnail3();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerTier;

};
