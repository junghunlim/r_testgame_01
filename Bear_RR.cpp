// Fill out your copyright notice in the Description page of Project Settings.


#include "Bear_RR.h"
#include "MyPlayerState.h"
#include "MyPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystem.h"
#include "r_testgameGameModeBase.h"

ABear_RR::ABear_RR() 
{
	bear_size = FVector(7, 7, 7);
	masskg = 2.0f;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> bear_skill(TEXT("/Game/FXVarietyPack/Particles/P_ky_lightning2"));
	if (bear_skill.Succeeded())
	{
		Bear_Skill_FX = bear_skill.Object;
	}
}
void ABear_RR::BeginPlay()
{
	Super::BeginPlay();

}

void ABear_RR::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABear_RR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//bear_rr 의 스킬
void ABear_RR::Skill_01()
{
	//크기와 무게를 20% 증가시킨다
	meshcomp2 = Cast<UStaticMeshComponent>(GetRootComponent());
	bear_size = FVector(bear_size.X * 1.2, bear_size.Y * 1.2, bear_size.Z * 1.2);
	meshcomp2->SetRelativeScale3D(FVector(bear_size.X, bear_size.Y, bear_size.Z));
	masskg = masskg * 1.2;
	meshcomp2->SetMassOverrideInKg("bear", masskg);

	//이펙트
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Bear_Skill_FX, GetActorLocation());

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			//게임모드 가져와서 cycle turn하여 컨트롤러의 end turn해서 다음턴으로 넘긴다
			auto MyGameMode = Cast<Ar_testgameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			MyGameMode->CycleTurn();

		}, 1, false);

}

void ABear_RR::NotifyActorOnClicked(FKey PressedButton)
{
	Super::NotifyActorOnClicked(PressedButton);

}
