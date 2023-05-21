
#include "AI_RR.h"
#include "MyAIController.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AAI_RR::AAI_RR()
{
 	
	AIControllerClass = AMyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorld;

	AICylinderComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderComponent"));
	AICylinderComponent->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder")).Object);

	AICylinderComponent->SetSimulatePhysics(true);
	AICylinderComponent->SetCollisionProfileName("oppspawn");
	AICylinderComponent->SetAngularDamping(0.1f);
	AICylinderComponent->SetLinearDamping(0.1f);
	AICylinderComponent->SetupAttachment(RootComponent);

}


void AAI_RR::MoveThisAIRR(FVector Force)
{
	meshcomp2 = Cast<UStaticMeshComponent>(GetRootComponent());
	meshcomp2->AddForce(Force * 500 * meshcomp2->GetMass());
}

int AAI_RR::CheckRRMove()
{
	meshcomp2 = Cast<UStaticMeshComponent>(GetRootComponent());
	if (meshcomp2->GetPhysicsLinearVelocity().IsNearlyZero())return 1;
	else return -1000;
}

// Called when the game starts or when spawned
void AAI_RR::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAI_RR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAI_RR::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

