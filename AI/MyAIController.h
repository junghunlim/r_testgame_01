// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class R_TESTGAME_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	

public:

	AMyAIController();

	void StartTurn();

	void EndTurn();

	UFUNCTION()
	void MoveAI_RR();

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

private:

	bool MyTurn;

	void SetMyTurn(bool myturn);

	UPROPERTY()
	class AAI_RR* currentAI_RR;

	UPROPERTY()
	class ABasic_RR* currentBasic_RR;

};
