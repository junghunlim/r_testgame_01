// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Basic_RR.h"
#include "Bear_RR.generated.h"

/**
 * 
 */
UCLASS()
class R_TESTGAME_API ABear_RR : public ABasic_RR
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABear_RR();

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
	UStaticMeshComponent* meshcomp2;

	UPROPERTY()
	class UParticleSystem* Bear_Skill_FX;

	float masskg;

	FVector bear_size;

	virtual void NotifyActorOnClicked(FKey PressedButton = EKeys::LeftMouseButton) override;
};
