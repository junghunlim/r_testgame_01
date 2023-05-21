// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "AI_RR.h"
#include "Basic_RR.h"
#include "r_testgameGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "MyPlayerController.h"
#include "MovementManager.h"

AMyAIController::AMyAIController()
{

}
void AMyAIController::StartTurn()
{
	MoveAI_RR();
}

void AMyAIController::EndTurn()
{

}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyAIController::MoveAI_RR()
{

	//AI_RR ADDFORCE 하기
	currentAI_RR = Cast<AAI_RR>(GetPawn());
	FVector airrloc = currentAI_RR->GetActorLocation();
	currentBasic_RR = Cast<ABasic_RR>(UGameplayStatics::GetActorOfClass(GetWorld(), ABasic_RR::StaticClass()));
	FVector basicrrloc = currentBasic_RR->GetActorLocation();
	FVector deltarrloc = basicrrloc - airrloc;
	FVector DeltaDirection(deltarrloc.X, deltarrloc.Y, 0);

	FVector Force = FVector(DeltaDirection.X, DeltaDirection.Y, 0.0f).GetSafeNormal() *30* 10;
	currentAI_RR->MoveThisAIRR(Force);

	//movementmanager 스폰해서 움직임 멈추면 CycleTurn()
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			AMovementManager* MovementManager = (AMovementManager*)GetWorld()->SpawnActor(AMovementManager::StaticClass());

		}, 0.5, false);

}

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMyAIController::SetMyTurn(bool myturn)
{
}
