// Fill out your copyright notice in the Description page of Project Settings.
//사용 안함

#include "Skill_Round.h"
#include "MyPlayerController.h"
#include <kismet/GameplayStatics.h>

// Sets default values
ASkill_Round::ASkill_Round()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Skill_Round_Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Skill_Round_Component"));
	Skill_Round_Component->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Skill/Skill_Range")).Object);
	Skill_Round_Component->SetSimulatePhysics(false);
	Skill_Round_Component->SetCollisionProfileName("UI");
	Skill_Round_Component->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASkill_Round::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_Round::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AMyPlayerController* controller = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (GEngine && GEngine->GameViewport)
	{
		//화살표의 크기정해주기
		GEngine->GameViewport->GetMousePosition(CurrentMousePosition);
		FVector2D MouseDelta(CurrentMousePosition.X - 518 , CurrentMousePosition.Y - 425 );

		//화살표의 방향 정해주기
		//여기 오류(마우스포지션 X,Y축 다름)가 있지만 일단 냅둠! 
		FVector MouseDeltaDirection(-MouseDelta.Y, MouseDelta.X, 0);

		
		FRotator InvertMouseDeltaRotator = FRotationMatrix::MakeFromZ(MouseDeltaDirection).Rotator();
		
		FRotator ArrowRotation = FRotator(InvertMouseDeltaRotator.Pitch, InvertMouseDeltaRotator.Yaw + 180, 0.0f);
		
		Skill_Round_Component->SetWorldRotation(ArrowRotation);

	}

}

