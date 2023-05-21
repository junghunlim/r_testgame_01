
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
			//ȭ��ǥ�� ũ�������ֱ�
			GEngine->GameViewport->GetMousePosition(CurrentMousePosition);
			MouseDelta = CurrentMousePosition - InitialMousePosition;
			float ArrowLength = MouseDelta.Size() / 4.0;

			//ȭ��ǥ �ִ� ���� ����
			if (ArrowLength > 22) {
				ArrowLength = 22;
			}

			FVector ArrowScale(1 * ArrowLength, 4, 4);
			ArrowComponent->SetRelativeScale3D(ArrowScale);

			//ȭ��ǥ�� ���� �����ֱ�
			FVector MouseDeltaDirection(MouseDelta.X, MouseDelta.Y, 0);			
			InvertMouseDeltaRotator = FRotationMatrix::MakeFromZ(MouseDeltaDirection).Rotator();
			FRotator ArrowRotation = FRotator(0.0f, InvertMouseDeltaRotator.Yaw, 0.0f);
			ArrowComponent->SetWorldRotation(ArrowRotation);

		}
	}
	if (controller->bClickLeftMouse == false && bClickMouse == true)
	{
		//ȭ��ǥ ����
		ArrowComponent->DestroyComponent();

		//�� �̵�
		if (rrmoveable == true)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("move!"));
			rrmoveable = false;

			//skill_eagle ����
			FVector pawnLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
			FVector arrowLocation(pawnLocation.X , pawnLocation.Y , pawnLocation.Z );
			FRotator SpawnRotation(InvertMouseDeltaRotator.Pitch, InvertMouseDeltaRotator.Yaw, 0.0f);
			ASkill_eagle_01* Projectile_eagle = (ASkill_eagle_01*)GetWorld()->SpawnActor(ASkill_eagle_01::StaticClass(), &arrowLocation, &SpawnRotation);
			Projectile_eagle->SetActorScale3D(FVector(10, 10, 10));

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
				{
					//���Ӹ�� �����ͼ� cycle turn�Ͽ� ��Ʈ�ѷ��� end turn�ؼ� ���������� �ѱ��
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

