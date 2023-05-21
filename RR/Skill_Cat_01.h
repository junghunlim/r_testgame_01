// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill_Cat_01.generated.h"

UCLASS()
class R_TESTGAME_API ASkill_Cat_01 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_Cat_01();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Skill_Cat_01_comp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void RotateThisActor();

	UFUNCTION()
	void OnHitActor(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FTimerHandle CountdownTimerHandle;

	FRotator CurrentRotation;

	int32 CountDown;

	UPROPERTY()
	class AAI_RR* currentAI_RR2;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
