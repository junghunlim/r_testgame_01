
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AI_RR.generated.h"

UCLASS()
class R_TESTGAME_API AAI_RR : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAI_RR();

	UFUNCTION()
	void MoveThisAIRR(FVector Force);

	UPROPERTY()
	UStaticMeshComponent* meshcomp2;

	int CheckRRMove();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* AICylinderComponent;


};
