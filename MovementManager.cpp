// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementManager.h"
#include <Kismet/GameplayStatics.h>
#include "AI_RR.h"
#include "Basic_RR.h"
#include "r_testgameGameModeBase.h"

// Sets default values
AMovementManager::AMovementManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

}

// Called when the game starts or when spawned
void AMovementManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovementManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	int checkint = 0;
	//basic_rr 가져와서 정지했는지 확인
	TArray<AActor*> tar_rr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasic_RR::StaticClass(), tar_rr);
	if (tar_rr.IsValidIndex(0))
	{
		for (int i = 0; i < tar_rr.Num(); i++) {
			auto current_rr = Cast<ABasic_RR>(tar_rr[i]);
			checkint += current_rr->CheckRRMove();
		}
	}
	//ai_rr 가져와서 정지했는지 확인

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAI_RR::StaticClass(), tar_rr);
	if (tar_rr.IsValidIndex(0))
	{
		for (int i = 0; i < tar_rr.Num(); i++) {
			auto currentAI_rr = Cast<AAI_RR>(tar_rr[i]);
			checkint += currentAI_rr->CheckRRMove();
		}
	}

	if (checkint > 0) {
		//cycleturn
		auto MyGameMode = Cast<Ar_testgameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		MyGameMode->CycleTurn();
		
		SetActorTickEnabled(false);
	}
}

