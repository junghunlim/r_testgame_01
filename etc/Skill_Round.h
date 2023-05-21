// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill_Round.generated.h"

UCLASS()
class R_TESTGAME_API ASkill_Round : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_Round();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Skill_Round_Component;

	FVector2D CurrentMousePosition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
