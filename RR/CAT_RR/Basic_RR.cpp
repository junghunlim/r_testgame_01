// Fill out your copyright notice in the Description page of Project Settings.


#include "Basic_RR.h"
#include "MyPlayerController.h"
#include "MyPlayerState.h"
#include "Skill_Cat_01.h"
#include <Kismet/GameplayStatics.h>
#include "AI_RR.h"

// Sets default values
ABasic_RR::ABasic_RR()
{

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Weight = 1;
	MovableDistance = 1.0f;
	AliveState = true;
	Mana = 1;

	CylinderComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderComponent"));
	CylinderComponent->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder")).Object);

	CylinderComponent->SetSimulatePhysics(true);
	CylinderComponent->SetCollisionProfileName("mypawn");
	CylinderComponent->SetAngularDamping(0.1f);
	CylinderComponent->SetLinearDamping(0.1f);
	CylinderComponent->SetupAttachment(RootComponent);

	//rrinfo
	RRLevel = 1;
	RRClass = FText::FromString("ClassName");
}

int32 ABasic_RR::GetRRLevel()
{
	return RRLevel;
}

FText ABasic_RR::GetRRClass()
{
	return RRClass;
}

UTexture2D* ABasic_RR::GetRRThumbnail()
{
	return RRThumbnail;
}

void ABasic_RR::BindPlayerRRState1(class AMyPlayerState* PlayerState2)
{
	CurrentPlayerRRState = PlayerState2;
	PlayerState2->OnPlayerStateChanged.AddUObject(this, &ABasic_RR::UpdatePlayerRRState1);
}

void ABasic_RR::UpdatePlayerRRState1()
{
	RRClass = CurrentPlayerRRState->GetRRClass1();
	RRThumbnail = CurrentPlayerRRState->GetRRThumbnail1();
	RRLevel = CurrentPlayerRRState->GetRRLevel1();
}

void ABasic_RR::BindPlayerRRState2(class AMyPlayerState* PlayerState2)
{
	CurrentPlayerRRState = PlayerState2;
	PlayerState2->OnPlayerStateChanged.AddUObject(this, &ABasic_RR::UpdatePlayerRRState2);
}

void ABasic_RR::UpdatePlayerRRState2()
{
	RRClass = CurrentPlayerRRState->GetRRClass2();
	RRThumbnail = CurrentPlayerRRState->GetRRThumbnail2();
	RRLevel = CurrentPlayerRRState->GetRRLevel2();
}

void ABasic_RR::BindPlayerRRState3(class AMyPlayerState* PlayerState2)
{
	CurrentPlayerRRState = PlayerState2;
	PlayerState2->OnPlayerStateChanged.AddUObject(this, &ABasic_RR::UpdatePlayerRRState3);
}

void ABasic_RR::UpdatePlayerRRState3()
{
	RRClass = CurrentPlayerRRState->GetRRClass3();
	RRThumbnail = CurrentPlayerRRState->GetRRThumbnail3();
	RRLevel = CurrentPlayerRRState->GetRRLevel3();
}

// Called when the game starts or when spawned
void ABasic_RR::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasic_RR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasic_RR::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasic_RR::MoveThisRR(FVector Force)
{
	meshcomp = Cast<UStaticMeshComponent>(GetRootComponent());
	meshcomp->AddForce(Force*200*meshcomp->GetMass());
}

//cat_rr 의 스킬
void ABasic_RR::Skill_01()
{
	//스킬 ui 생성
	FVector pawnLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector cat_foot_Location(pawnLocation.X, pawnLocation.Y, pawnLocation.Z + 30);

	//두 백터사잇각 구해서 +90만큼 돌린위치에 spawn하기
	auto ai_rr = Cast<AAI_RR>(UGameplayStatics::GetActorOfClass(GetWorld(), AAI_RR::StaticClass()));
	FVector airrLocation = ai_rr->GetActorLocation();
	FVector aaloc = airrLocation - pawnLocation;
	FVector bbloc(0, 150, 0);

	float cc = FindInteriorAngle(aaloc, bbloc);

	FRotator SpawnRotation(0, cc + 90, 0);

	//Skill_Cat_01 spawn
	ASkill_Cat_01* Skill_Cat_01 = (ASkill_Cat_01*)GetWorld()->SpawnActor(ASkill_Cat_01::StaticClass(), &cat_foot_Location, &SpawnRotation);

}

float ABasic_RR::FindInteriorAngle(FVector A, FVector B)
{
	float DotProduct = FVector::DotProduct(A, B);
	float LengthA = A.Size();
	float LengthB = B.Size();

	float AngleRadians = FMath::Acos(DotProduct / (LengthA * LengthB));
	float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);

	return AngleDegrees;
}

void ABasic_RR::NotifyActorOnClicked(FKey PressedButton)
{
	Super::NotifyActorOnClicked(PressedButton);

	//컨트롤러 가져와서 명령위젯 보여주는함수 실행 
	AMyPlayerController* controller = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->RemoveOrderWidget();
	controller->Possess(this);
	controller->ShowOrderWidget();
}

int ABasic_RR::CheckRRMove()
{
	meshcomp = Cast<UStaticMeshComponent>(GetRootComponent());
	if (meshcomp->GetPhysicsLinearVelocity().IsNearlyZero())return 1;
	else return -1000;
}
