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


	//����
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

	//���԰�
	UPROPERTY(EditAnywhere)
	float Weight;

	//�̵����ɰŸ�
	UPROPERTY(EditAnywhere)
	int32 MovableDistance;

	//�׾����� ��Ҵ��� ����
	UPROPERTY(EditAnywhere)
	bool AliveState;

	//��ų ��밡��Ƚ��
	UPROPERTY(EditAnywhere)
	int32 Mana;

	//���̰��ϴ°� ����
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
