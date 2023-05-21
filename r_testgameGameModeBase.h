// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "r_testgameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class R_TESTGAME_API Ar_testgameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	Ar_testgameGameModeBase();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	void CycleTurn();

protected:

	virtual void BeginPlay() override;

	void StartGame();

private:

	int8 CurrentPlayerTurn = 0;
};
