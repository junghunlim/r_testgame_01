// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyArrow.generated.h"

UCLASS()
class R_TESTGAME_API AMyArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyArrow();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ArrowComponent;

	FVector2D InitialMousePosition;

	FVector2D CurrentMousePosition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	virtual void NotifyActorOnClicked(FKey PressedButton = EKeys::LeftMouseButton) override;

	bool rrmoveable;

	bool bClickMouse;

	FVector2D MouseDelta;
};
