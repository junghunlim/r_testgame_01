// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCameraDirector.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMyCameraDirector::AMyCameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (OurPlayerController)
	{
		if (OurPlayerController->GetViewTarget() != MyCamera)
		{
			OurPlayerController->SetViewTarget(MyCamera);
		}
	}

}

