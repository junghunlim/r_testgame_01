
#include "Arrow_Eagle_Skill.h"
#include "MyPlayerController.h"
#include <kismet/GameplayStatics.h>
#include "Math/Rotator.h"
#include "Skill_eagle_01.h"
#include "r_testgameGameModeBase.h"

// Sets default values
AArrow_Eagle_Skill::AArrow_Eagle_Skill()
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
void AArrow_Eagle_Skill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArrow_Eagle_Skill::Tick(float DeltaTime)
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
			float ArrowLength = MouseDelta.Size() / 4.0;

			//화살표 최대 길이 고정
			if (ArrowLength > 22) {
				ArrowLength = 22;
			}

			FVector ArrowScale(1 * ArrowLength, 4, 4);
			ArrowComponent->SetRelativeScale3D(ArrowScale);

			//화살표의 방향 정해주기
			FVector MouseDeltaDirection(MouseDelta.X, MouseDelta.Y, 0);			
			InvertMouseDeltaRotator = FRotationMatrix::MakeFromZ(MouseDeltaDirection).Rotator();
			FRotator ArrowRotation = FRotator(0.0f, InvertMouseDeltaRotator.Yaw, 0.0f);
			ArrowComponent->SetWorldRotation(ArrowRotation);

		}
	}
	if (controller->bClickLeftMouse == false && bClickMouse == true)
	{
		//화살표 제거
		ArrowComponent->DestroyComponent();

		//폰 이동
		if (rrmoveable == true)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("move!"));
			rrmoveable = false;

			//skill_eagle 실행
			FVector pawnLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
			FVector arrowLocation(pawnLocation.X , pawnLocation.Y , pawnLocation.Z );
			FRotator SpawnRotation(InvertMouseDeltaRotator.Pitch, InvertMouseDeltaRotator.Yaw, 0.0f);
			ASkill_eagle_01* Projectile_eagle = (ASkill_eagle_01*)GetWorld()->SpawnActor(ASkill_eagle_01::StaticClass(), &arrowLocation, &SpawnRotation);
			Projectile_eagle->SetActorScale3D(FVector(10, 10, 10));

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
				{
					//게임모드 가져와서 cycle turn하여 컨트롤러의 end turn해서 다음턴으로 넘긴다
					auto MyGameMode = Cast<Ar_testgameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
					MyGameMode->CycleTurn();

				}, 4.0, false);

		}

		bClickMouse = false;
	}
}

void AArrow_Eagle_Skill::NotifyActorOnClicked(FKey PressedButton)
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

