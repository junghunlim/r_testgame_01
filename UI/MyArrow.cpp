// Fill out your copyright notice in the Description page of Project Settings.


#include "MyArrow.h"
#include "Components/ArrowComponent.h"
#include "MyPlayerController.h"
#include <kismet/GameplayStatics.h>
#include "Math/Rotator.h"


// Sets default values
AMyArrow::AMyArrow()
{
 	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	ArrowComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Image/Arrow5")).Object);
	ArrowComponent->SetSimulatePhysics(false);
	ArrowComponent->SetCollisionProfileName("UI");
	ArrowComponent->SetupAttachment(RootComponent);

	bClickMouse = false;
	rrmoveable = true;
}


// Called when the game starts or when spawned
void AMyArrow::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AMyPlayerController* controller = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (controller->bClickLeftMouse == true && bClickMouse == true)
	{
		if (GEngine && GEngine->GameViewport)
		{
			//화살표의 크기정해주기
			GEngine->GameViewport->GetMousePosition(CurrentMousePosition);
			MouseDelta = CurrentMousePosition - InitialMousePosition;
			float ArrowLength = MouseDelta.Size() / 4.0 ;

			//화살표 최대 길이 고정
			if (ArrowLength > 25) {
				ArrowLength = 25;
			}

			FVector ArrowScale(1 * ArrowLength, 4, 4);
			ArrowComponent->SetRelativeScale3D(ArrowScale);
			
			//화살표의 방향 정해주기
			FVector MouseDeltaDirection(MouseDelta.X, MouseDelta.Y , 0);
			FRotator InvertMouseDeltaRotator = FRotationMatrix::MakeFromZ(MouseDeltaDirection).Rotator();
			FRotator ArrowRotation = FRotator(0.0f, InvertMouseDeltaRotator.Yaw, 0.0f);
			ArrowComponent->SetWorldRotation(ArrowRotation);

		}
	}
	if(controller->bClickLeftMouse == false && bClickMouse == true)
	{
		//화살표 제거
		ArrowComponent->DestroyComponent();

		//폰 이동
		if (rrmoveable == true)
		{
			rrmoveable = false;
			
			//화살표 최대 길이에 비례한 최대 force 고정 
			if (MouseDelta.Size() > 100.0) {
				MouseDelta = MouseDelta*(100.0/MouseDelta.Size());
			}
			controller->MoveRR(MouseDelta);
		}

		bClickMouse = false;
	}

}


void AMyArrow::NotifyActorOnClicked(FKey PressedButton)
{
	Super::NotifyActorOnClicked(PressedButton);

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetMousePosition(InitialMousePosition);
	}

	AMyPlayerController* controller = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->bClickLeftMouse = true;

	bClickMouse = true;
}

