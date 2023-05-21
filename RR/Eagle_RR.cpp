// Fill out your copyright notice in the Description page of Project Settings.

#include "Eagle_RR.h"
#include "Arrow_Eagle_Skill.h"
#include "MyPlayerController.h"

AEagle_RR::AEagle_RR()
{

}
void AEagle_RR::BeginPlay()
{
	Super::BeginPlay();
}

void AEagle_RR::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEagle_RR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEagle_RR::Skill_01()
{
	//arrow_eagle_skill spawnÇÑ´Ù
	FVector pawnLocation = GetActorLocation();
	FVector arrowLocation(pawnLocation.X, pawnLocation.Y, pawnLocation.Z + 60);
	FRotator SpawnRotation(0, 0, 0);
	AArrow_Eagle_Skill* SpawnedArrow2 = (AArrow_Eagle_Skill*)GetWorld()->SpawnActor(AArrow_Eagle_Skill::StaticClass(), &arrowLocation, &SpawnRotation);
	SpawnedArrow2->SetActorScale3D(FVector(8, 6, 5));
}
