// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h>
#include "Skill_eagle_01.generated.h"

UCLASS()
class R_TESTGAME_API ASkill_eagle_01 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_eagle_01();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHitActor(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY()
	class AActor* currentAI_RR3;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* collisioncomp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY()
	UParticleSystemComponent* OurParticleSystemcomp;

};
