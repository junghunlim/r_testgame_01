// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_Cat_01.h"
#include "AI_RR.h"
#include "r_testgameGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "Basic_RR.h"

// Sets default values
ASkill_Cat_01::ASkill_Cat_01()
{

	Skill_Cat_01_comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Skill_Cat_01_comp"));
	Skill_Cat_01_comp->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Skill/Skill_Cat_01")).Object);
	
	Skill_Cat_01_comp->SetSimulatePhysics(true);
	Skill_Cat_01_comp->SetEnableGravity(false);
	Skill_Cat_01_comp->SetNotifyRigidBodyCollision(true);
	Skill_Cat_01_comp->SetCollisionProfileName("Skill_ToPawn");
	Skill_Cat_01_comp->SetAngularDamping(0.1f);
	Skill_Cat_01_comp->SetLinearDamping(0.1f);
	Skill_Cat_01_comp->SetMassOverrideInKg("cat_foot",50.0f);
	Skill_Cat_01_comp->SetupAttachment(RootComponent);
	CountDown = 30;
}

// Called when the game starts or when spawned
void ASkill_Cat_01::BeginPlay()
{
	Super::BeginPlay();

	Skill_Cat_01_comp->SetRelativeScale3D(FVector(1, 1.25, 1));	

	Skill_Cat_01_comp->OnComponentHit.AddDynamic(this, &ASkill_Cat_01::OnHitActor);

	// TestFunction 을 초당 0.04 회, 처음 0.7 초후에 호출합니다.
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ASkill_Cat_01::RotateThisActor, 0.04f, true, 0.7f);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			//게임모드 가져와서 cycle turn하여 컨트롤러의 end turn해서 다음턴으로 넘긴다
			auto MyGameMode = Cast<Ar_testgameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			MyGameMode->CycleTurn();

		}, 2.5, false);

}

void ASkill_Cat_01::RotateThisActor()
{
	CurrentRotation = GetActorRotation();
	FRotator NewRotation = CurrentRotation + FRotator(0.0f, 20.0f, 0.0f);

	// Set the new rotation of the actor
	SetActorRotation(NewRotation);

	// 타이머 해제
	--CountDown;
	if (CountDown <= 0)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		Skill_Cat_01_comp->DestroyComponent();
	}
	
}

void ASkill_Cat_01::OnHitActor(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	Skill_Cat_01_comp->DestroyComponent();
	
	//addfoce 해주기
	FVector HitLocation = Hit.ImpactPoint;
	FVector ActorLocation = OtherActor->GetActorLocation();
	FVector ForceDirection = ActorLocation - HitLocation;
	FVector Force = FVector(ForceDirection.X, ForceDirection.Y, 0.0f).GetSafeNormal() * 30 * 10;

	currentAI_RR2 = Cast<AAI_RR>(OtherActor);
	currentAI_RR2->MoveThisAIRR(Force);

}

// Called every frame
void ASkill_Cat_01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

