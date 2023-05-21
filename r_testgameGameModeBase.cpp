// Copyright Epic Games, Inc. All Rights Reserved.


#include "r_testgameGameModeBase.h"
#include "MyPlayerState.h"
#include "MyPlayerController.h"
#include "MyAIController.h"
#include <Kismet/GameplayStatics.h>
#include "AI_RR.h"
#include "Basic_RR.h"

Ar_testgameGameModeBase::Ar_testgameGameModeBase()
{
	PlayerStateClass = AMyPlayerState::StaticClass();
}
void Ar_testgameGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	//playerstate init���ֱ�
	auto MyPlayerState = Cast<AMyPlayerState>(NewPlayer->PlayerState);
	MyPlayerState->InitPlayerData();
	MyPlayerState->InitPlayerRRData();
	
}
void Ar_testgameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	StartGame();
}

void Ar_testgameGameModeBase::StartGame()
{
	//��Ʈ�ѷ� �ҷ��ͼ� startturn �Լ� �ҷ�����
	auto MyPlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	MyPlayerController->StartTurn();
}

void Ar_testgameGameModeBase::CycleTurn()
{

	//���� PLAYER ���϶�
	if (CurrentPlayerTurn == 0)
	{
		//��Ʈ�ѷ� �ҷ��ͼ� endturn �Լ� �ҷ�����
		auto MyPlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
		MyPlayerController->EndTurn();

		if (UGameplayStatics::GetActorOfClass(GetWorld(), ABasic_RR::StaticClass()) != nullptr && UGameplayStatics::GetActorOfClass(GetWorld(), AAI_RR::StaticClass()) != nullptr)
		{
			//ai��Ʈ�ѷ� �ҷ��ͼ� startturn �Լ� �ҷ����� 
			auto ai_rr = Cast<AAI_RR>(UGameplayStatics::GetActorOfClass(GetWorld(), AAI_RR::StaticClass()));
			AMyAIController* MyAiController = Cast<AMyAIController>(ai_rr->GetController());
			MyAiController->StartTurn();
		}

		CurrentPlayerTurn = 1;

	}
	else
	{
		auto MyPlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
		MyPlayerController->CheckGameScore();

		if (UGameplayStatics::GetActorOfClass(GetWorld(), ABasic_RR::StaticClass()) != nullptr && UGameplayStatics::GetActorOfClass(GetWorld(), AAI_RR::StaticClass()) != nullptr)
		{
			//MYPLAYERCONTROLLER �����ͼ� STARTTURN
			MyPlayerController->StartTurn();
		}


		CurrentPlayerTurn = 0;
	}

}

