// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Basic_RR.h"
#include "Eagle_RR.generated.h"

/**
 * 
 */
UCLASS()
class R_TESTGAME_API AEagle_RR : public ABasic_RR
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEagle_RR();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Skill_01() override;

private:
	UPROPERTY()
	UStaticMeshComponent* meshcomp3;

};
