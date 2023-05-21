// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Basic_RR.generated.h"

UCLASS()
class R_TESTGAME_API ABasic_RR : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasic_RR();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveThisRR(FVector Force);

	UPROPERTY()
	UStaticMeshComponent* meshcomp;


	//변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText RRClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* RRThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RRLevel;

	//rrinfo
	int32 GetRRLevel();
	FText GetRRClass();
	UTexture2D* GetRRThumbnail();

	void UpdatePlayerRRState1();
	void BindPlayerRRState1(class AMyPlayerState* PlayerState2);

	void UpdatePlayerRRState2();
	void BindPlayerRRState2(class AMyPlayerState* PlayerState2);

	void UpdatePlayerRRState3();
	void BindPlayerRRState3(class AMyPlayerState* PlayerState2);

	TWeakObjectPtr<class AMyPlayerState> CurrentPlayerRRState;

	//무게감
	UPROPERTY(EditAnywhere)
	float Weight;

	//이동가능거리
	UPROPERTY(EditAnywhere)
	int32 MovableDistance;

	//죽었는지 살았는지 상태
	UPROPERTY(EditAnywhere)
	bool AliveState;

	//스킬 사용가능횟수
	UPROPERTY(EditAnywhere)
	int32 Mana;

	//보이게하는거 더미
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CylinderComponent;

	virtual void Skill_01();

	float FindInteriorAngle(FVector A, FVector B);

	virtual void NotifyActorOnClicked(FKey PressedButton = EKeys::LeftMouseButton) override;

	int CheckRRMove();

private:

};
