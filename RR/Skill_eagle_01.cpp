// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_eagle_01.h"
#include "Particles/ParticleSystem.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystemComponent.h"
#include "AI_RR.h"

// Sets default values
ASkill_eagle_01::ASkill_eagle_01()
{
 	//collisioncomp 생성 및 설정
	collisioncomp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("collisioncomp"));
	collisioncomp->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/FXVarietyPack/Meshes/SM_ky_tornado07")).Object);
	
	UMaterialInterface* NewMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/FXVarietyPack/Materials/MI_ky_storm01_aqua"));
	collisioncomp->SetMaterial(0, NewMaterial);

	//ParticleSystemcomp 생성 및 설정
	OurParticleSystemcomp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("OurParticleSystemcomp"));
	OurParticleSystemcomp->SetupAttachment(collisioncomp);
	OurParticleSystemcomp->bAutoActivate = true;
	OurParticleSystemcomp->SetRelativeScale3D(FVector(0.05,0.05,0.1));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/FXVarietyPack/Particles/P_ky_aquaStorm_2"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystemcomp->SetTemplate(ParticleAsset.Object);
	}


	//collisioncomp 설정
	collisioncomp->SetSimulatePhysics(true);
	collisioncomp->SetEnableGravity(false);
	collisioncomp->SetNotifyRigidBodyCollision(true);
	collisioncomp->SetCollisionProfileName("Skill_ToPawn");
	collisioncomp->SetAngularDamping(0.1f);
	collisioncomp->SetLinearDamping(0.1f);
	collisioncomp->SetMassOverrideInKg("skill_eagle", 10.0f);
	RootComponent = collisioncomp;

	//ProjectileMovementComp 생성 및 설정
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->SetUpdatedComponent(collisioncomp);
	ProjectileMovementComp->InitialSpeed = 1000.0f;
	ProjectileMovementComp->MaxSpeed = 3000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bShouldBounce = false;
	
	InitialLifeSpan = 10.0f;

}



// Called when the game starts or when spawned
void ASkill_eagle_01::BeginPlay()
{
	Super::BeginPlay();

	collisioncomp->OnComponentHit.AddDynamic(this, &ASkill_eagle_01::OnHitActor);


}

void ASkill_eagle_01::OnHitActor(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//스킬 제거
	RootComponent->DestroyComponent();
	ProjectileMovementComp->DestroyComponent();
	OurParticleSystemcomp->DestroyComponent();

	//add impulse,torque 
	FVector Force = FVector(0,0,1).GetSafeNormal() * 2 * 10;

	FVector HitLocation = Hit.ImpactPoint;
	FVector ActorLocation = OtherActor->GetActorLocation();
	FVector ForceDirection = ActorLocation - HitLocation;

	auto meshcomp3 = Cast<UStaticMeshComponent>(OtherActor->GetRootComponent());
	meshcomp3->AddImpulse(Force * 5 * meshcomp3->GetMass());
	meshcomp3->AddTorque(ForceDirection * 2000 * 300 * 20);

}

// Called every frame
void ASkill_eagle_01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

